#!/bin/bash

#SECTION - global variables

readonly G_TARGET_DIR="./real-tests"
readonly G_BACKUP_DIR="./backup"
readonly G_CONFIG_FILE="./setup_test.ini"
readonly G_MAKEFILE="$G_TARGET_DIR/Makefile"
readonly G_HEADER_NAME="tests.h"
readonly G_HEADER="$G_TARGET_DIR/$G_HEADER_NAME"
readonly G_MAIN="$G_TARGET_DIR/main.c"
readonly G_LAUNCHER_NAME="launcher"
export USER="alerusso"
#@type {Map<module_name, Array<test_name>>}
declare -A G_MODULES=()

#SECTION - utilities


LIBUNITlog_info()	{ echo -e "\033[1;34m[INFO]\033[0m $1"; }
LIBUNITlog_success(){ echo -e "\033[1;32m[SUCCESS]\033[0m $1"; }
LIBUNITlog_warn()	{ echo -e "\033[1;33m[WARNING]\033[0m $1"; }
LIBUNITlog_error()	{ echo -e "\033[1;31m[ERROR]\033[0m $1"; }

#@description signal handler given to trap
#@param {number} $1:LINENO 			last executed line in script
#@param {string} $2:BASH_COMMAND 	last command executed
LIBUNITcatch_error()
{
	LIBUNITlog_error "line $1: '$2'" >&2
	exit 1
}

#@description prints an error and exits
#@param {string} $1:message
LIBUNITerror()
{
	LIBUNITlog_error "$1" >&2
	exit 1
}

LIBUNITutils_setup()
{
	set -e		#DOC	=> e: exit on errors (check only )
	set -u		#DOC	=> u:track undefined variables
	set -E		#DOC	=> E:track functions
	#set -x		#DEBUG	=> x: prints every command run
	mkdir -p "$G_TARGET_DIR"
	mkdir -p "$G_BACKUP_DIR"
	#DOC	=> trap is like UNIX signal with argument handling
	#DOC	=> LINENO:last executed line in script
	#DOC	=> BASH_COMMAND: last command executed
	trap 'LIBUNITcatch_error ${LINENO} "${BASH_COMMAND}"' ERR 
	if test "$USER" = "" || test "$USER" = "codespace";then
		LIBUNITerror "Variable HOST unset. Set it at the top of this script"
	fi
}

#@description creates a string of n spaces
#@param {number} $1:spaces	number of spaces
#@print {string} n_spaces_string
LIBUNITutils_putspace()
{
	local	str=""
	local	spaces;

	set +u	#DOC	=>	deactivates undefined variable check
	if (($1 < 0));then
		spaces="0"
	else
		spaces="$1"
	fi
	set -u
	for ((i = 0; i != "$spaces"; i++)); do
		str="$str "
	done
	echo "$str"
}

#@description creates a string of n spaces
#@param {string} $1:str		str to trim
#@param {number} $2:from	starting pos DEFAULT: 0
#@param {number} $3:to		end pos	DEFAULT: str.length
#@print {string} trimmed_str
LIBUNITutils_strtrim()
{
	local	str;
	local	from;
	local	to;

	set +u
	if test "$2" = "";then
		((from = 0))
	else
		((from = "$2"))
	fi
	if test "$3" = "";then
		((to = "${#1}"))
	else
		((to = "$3"))
	fi
	set -u
	str="$1"
	str="${str:$from:$to}"
	echo "$str"
}

#@description index a number, adding trailing 0 if needed
#@param {number} $1:counter
#@print {string} indexed_number	0=>00; 7=>07; 42=>42
LIBUNITutils_index_number()
{
	local	counter=$1

	(($counter < 0)) && counter="0"
	(($counter < 10)) && counter="0$counter"
	echo "$counter"
}

#@description format a filename with xx_testname.c
#@param {string} $1:testname
#@param {number} $2:counter
#@print {string} indexed_testname	xx_testname.c
LIBUNITutils_index_file()
{
	local	testname=$1

	echo "$(LIBUNITutils_index_number $2)""_$testname.c" 
}

#@description get the full filepath
#@param {string} $1:testname
#@param {number} $2:counter
#@param {string} $3:module
#@print {string} path	./real_tests/testmod/xx_testname.c
LIBUNITutils_get_testpath()
{
	local	testname
	local	module=$3

	testname="$(LIBUNITutils_index_file "$1" "$2")"
	echo "$G_TARGET_DIR/$module/$testname" 
}

#@description get the full filepath in the backup dir
#@param {string} $1:testname
#@param {number} $2:counter
#@param {string} $3:module
#@print {string} path	./real_tests/testmod/xx_testname.c
LIBUNITutils_get_backpath()
{
	local	testname
	local	module=$3

	testname="$(LIBUNITutils_index_file "$1" "$2")"
	echo "$G_BACKUP_DIR/$module/$testname" 
}

#@description gives back a string with 42 header
#@param {string} filename
#@print {string} 42header
LIBUNITutils_42header()
{
	local test_file="$1"
	local sp0=$((51 - ${#test_file}))
	local sp1=$((26 - (${#USER} * 2)))
	local sp2=$((20 - ${#USER}))
	local sp3=$((17 - ${#USER}))

	sp0=$(LIBUNITutils_putspace $sp0)
	sp1=$(LIBUNITutils_putspace $sp1)
	sp2=$(LIBUNITutils_putspace $sp2)
	sp3=$(LIBUNITutils_putspace $sp3)
	cat << EOF
/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ${test_file}$sp0:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: $USER <$USER@student.42.fr>$sp1+#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: $(date +'%Y/%m/%d %H:%M:%S') by $USER$sp2#+#    #+#           */
/*   Updated: $(date +'%Y/%m/%d %H:%M:%S') by $USER$sp3###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
EOF
}

#@description run a function for every test. First arg is counter
#@param {function} filename
#@print {...} args
LIBUNITutils_foreach_test()
{
	local	func
	local	counter
	local	counter_indexed
	local	ret

	func="$1"
	ret=""
	for module in "${!G_MODULES[@]}";do
		tests="${G_MODULES["$module"]}"
		counter=0
		for test in $tests;do
			((counter++)) || ((1))
			counter_indexed="$(LIBUNITutils_index_number $counter)"
			"$func" "$counter_indexed" "$module" "$test"
		done
	done
	echo "$ret"
}

#@description run a function for every test. First arg is counter
#@param {function} filename
#@print {...} args
LIBUNITutils_foreach_module()
{
	local	func
	local	counter
	local	counter_indexed
	local	ret

	func="$1"
	ret=""
	counter=0
	for module in "${!G_MODULES[@]}";do
		((counter++)) || ((1))
		tests="${G_MODULES["$module"]}"
		counter_indexed="$(LIBUNITutils_index_number $counter)"
		"$func" "$counter_indexed" "$module"
	done
	echo "$ret"
}

#SECTION - format output

#@param {number} counter
#@param {string} module
#@param {string} test
#@print {...} int	modulename_testname(void);
LIBUNITformat_header()
{
	if test "$1" = "01";then
		echo "//SECTION - $2"
	fi
	echo "int	${2}_${1}_${3}(void);"
}

#@param {number} counter
#@param {string} module
#@param {string} test
#@print {...} int	modulename_testname(void);
LIBUNITformat_main()
{
	local	module="$2"

	echo "	output -= ${module}_launcher();"
}

LIBUNITformat_launcher()
{
	local	filepath
	local	header42
	local	files
	local	tests
	local	counter
	local	counter_indexed
	local	module
	local	module_upper

	module="$2"
	module_upper="${module^^}"
	filepath="$(LIBUNITutils_get_testpath launcher "0" "$module")"
	header42="$(LIBUNITutils_42header "00_launcher.c")"
	tests="${G_MODULES["$module"]}"
	counter=0
	files=""
	for test in $tests;do
		((counter++)) || ((1))
		counter_indexed="$(LIBUNITutils_index_number $counter)"
		files="$files""
	load_test(&list, \"${test}\", ${module}_${counter_indexed}_${test});"

	done
	cat > "$filepath" << EOF
${header42}

#include "../tests.h"

int	${module}_launcher(void)
{
	t_test_list	list;

	list = (t_test_list){0};${files}
	return (launch_tests(&list, "${module_upper}"));
}
EOF
}

#SECTION - configuration file

LIBUNITconf_create()
{
	touch "$G_CONFIG_FILE"
	cat > "$G_CONFIG_FILE" << EOF
#module1
[
	basic
	other
	null
]

#module2
[
	basic
	other
	null
]

EOF
	LIBUNITerror "Please edit the file $G_CONFIG_FILE and try again."
}

LIBUNITconf_parse()
{
	local	counter=-1
	local	mod_name=""
	local	tests=""
	local	start=""

	# set -x
	test -f "$G_CONFIG_FILE" || LIBUNITconf_create
	#DOC	=> read -r: read \ characters as they are
	#DOC	=> test -n: check if string is nonzero
	while read -r line || test -n "$line"; do
		((counter++)) || ((1))
		start="${line:0:1}"
		#DOC=> %: trim this at the end
		#DOC=> why? portability with files that comes from Windows
		line="${line%$'\r'}"
		if test "$line" = "" || test "$start" = ";" || test "$start" = "["; then
			continue;
		elif test -n "$mod_name" && test "$start" = "#";then
			LIBUNITerror "conf_parse, line $counter:unclosed module $mod_name"
		elif test "$start" = "#";then	#DOC	=> create new test module
			mod_name=$(LIBUNITutils_strtrim "$line" 1)
		elif test "$start" = "]";then	#DOC	=> close current test module
			G_MODULES["$mod_name"]="$tests"
			mod_name=""
			tests=""
		elif test "$mod_name" = "";then
			LIBUNITerror "conf_parse, line $counter:undefined module"
		elif test "$line" = "$G_LAUNCHER_NAME";then
			LIBUNITerror "conf_parse, line $counter:$G_LAUNCHER_NAME is reserved"
		else	#DOC	=> push to current test array
			tests="$tests $line"
		fi
	done < "$G_CONFIG_FILE"
	echo "Parse OK!"
	# set +x
}

#SECTION - sync #handles file replace, rename, ecc.

#@description save a file in the backup directory
#@param {string} $1:testname
#@param {number} $2:counter
#@param {string} $3:module
LIBUNITsync_backup_files()
{
	local	path
	local	backup
	local	backup_len
	local	counter

	path="$(LIBUNITutils_get_testpath "$1" "$2" "$3")"
	test -f "$path" || return ;
	mkdir -p "$G_BACKUP_DIR/$3"
	backup="$(LIBUNITutils_get_backpath "$1" "$2" "$3")"
	counter=1
	while test -f "$backup";do
		backup_len="$((("${#backup}" - 2)))"	#DOC	=> trim .c
		backup="$(LIBUNITutils_strtrim "$backup" "$backup_len")"
		backup="$G_BACKUP_DIR/$backup""_$counter.c"
		((++counter))
	done
	cp "$path" "$backup"
}

LIBUNITsync_rename_files()
{
	local	real_files=()
	local	setup_files=()
	local	counter
	local	path

	set +u
	for module in "${!G_MODULES[@]}";do
		real_files=("$(ls "$G_TARGET_DIR/$module")")
		setup_files=("${G_MODULES["$module"]}")
		counter=-1
		for setup_file in "${setup_files[@]}";do
			((counter++)) || ((1))
			for real_file in "${real_files[@]}";do
				if test "$(echo "$real_file" | grep ".*_$setup_file.c"; echo $?)" = "0";then
					path="$(LIBUNITutils_get_testpath "$setup_file" "$counter" "$mod_name")"
					LIBUNITsync_backup_files "$setup_file" "$counter" "$mod_name"
					cp "$real_file" "$path"
					rm -f "$real_file"
				fi
			done
		done
	done
	set -u
}

#SECTION - creation

#@description generates a template for the test
#@param {string} $1:testname
#@param {number} $2:counter
#@param {string} $3:module
LIBUNITcreate_test_template()
{
	local test_name="$1"
	local counter=$(LIBUNITutils_index_number $2)
	local test_file="$counter""_$1.c"
	local module="$3"
	local proto="int	$module""_$counter""_$test_name(void)"
	local path="$(LIBUNITutils_get_testpath "$1" $2 "$3")"
	local header="$(LIBUNITutils_42header "$test_file")"

	test -f "$path" && return ; 
	mkdir -p "$G_TARGET_DIR/$module/"
    cat > "$path" << EOF
${header}

#include "../tests.h"

${proto}
{
	return (-(${module}() != 0));
}
EOF
}

LIBUNITcreate_files()
{
	local	tests
	local	path
	local	counter

	for module in "${!G_MODULES[@]}";do
		tests="${G_MODULES["$module"]}"
		counter="0"
		for test in $tests;do
			((counter++)) || ((1))
			path="$(LIBUNITutils_get_testpath "$test" "$counter" "$module")"
			test -f "$path" && LIBUNITsync_backup_files "$test" "$counter" "$module"
			LIBUNITcreate_test_template "$test" "$counter" "$module"
		done
	done
}

LIBUNITcreate_makefile()
{
	local	files
	local	tests

	files="SRC = main.c"
	for module in "${!G_MODULES[@]}";do
		files="$files"'\
	$(addprefix '"$module"'/, $(shell ls '"$module"' | grep '\''\.c'\''))'
	done
	cat > "$G_MAKEFILE" << EOF
${files}
NAME = test.out
LIBUNIT = ../libunit.a
OBJ = \$(SRC:.c=.o)
COMP = cc -g -Wall -Werror -Wextra

all: \$(NAME)
	
\$(NAME) : \$(LIBUNIT) \$(OBJ) 
	echo \$(SRC)
	\$(COMP) \$(OBJ) \$(LIBUNIT) -o \$(NAME)

\$(LIBUNIT):
	\$(MAKE) -C ../

%.o: %.c
	\$(COMP) -c \$< -o \$@

clean: 
	rm -f \$(OBJ) \$(OBJ_BONUS) *.out

fclean: clean
	rm -f \$(NAME)

re: fclean all

test: all
	./\$(NAME)

val: all
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --child-silent-after-fork=yes --trace-children=no --track-fds=yes  -s ./\$(NAME)

.PHONY: all clean fclean re test
.SILENT:
EOF
}

LIBUNITcreate_header()
{
	local	header42
	local	files

	header42="$(LIBUNITutils_42header $G_HEADER_NAME)"
	files="$(LIBUNITutils_foreach_test LIBUNITformat_header)"
	echo "$files"
	cat > "$G_HEADER" << EOF
${header42}

#ifndef TESTS_H
# define TESTS_H

# include "../framework/libunit.h"

${files}

#endif
EOF
}

LIBUNITcreate_main()
{
	local	header42
	local	files

	header42="$(LIBUNITutils_42header $G_HEADER_NAME)"
	files="$(LIBUNITutils_foreach_module LIBUNITformat_main)"
	cat > "$G_MAIN" << EOF
${header42}

#include "tests.h"

int	main(void)
{
	int	output;

	output = 0;
${files}
	if (output == 0)
		write(1, "\033[1;32mTEST OK.\n\033[0m", 18);
	else
		write(1, "\033[1;31mTEST KO.\n\033[0m", 18);
	return (-(output != 0));
}

EOF
}

LIBUNITcreate_launcher()
{
	LIBUNITutils_foreach_module LIBUNITformat_launcher
}

#SECTION - main

LIBUNITmain()
{
	LIBUNITutils_setup
	LIBUNITconf_parse
	# LIBUNITsync_backup_files
	LIBUNITcreate_files
	LIBUNITcreate_makefile
	LIBUNITcreate_header
	LIBUNITcreate_main
	LIBUNITcreate_launcher
	for module in "${!G_MODULES[@]}";do
		echo "$module:	" "${G_MODULES["$module"]}"
	done
}

LIBUNITmain "$@"