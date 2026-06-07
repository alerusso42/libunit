#!/bin/bash

#SECTION - global variables

readonly G_TARGET_DIR="./real-tests"
readonly G_BACKUP_DIR="./backup"
readonly G_CONFIG_FILE="./setup_test.ini"
readonly G_LAUNCHER_NAME="launcher"
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
	local test_file="$2""_$1.c"
	local counter=$(LIBUNITutils_index_number $2)
	local module="$3"
	local proto="int	$module""253_$counter""_$test_name(void)"
	local path="$(LIBUNITutils_get_testpath "$1" $2 "$3")"
	local sp0=$((51 - ${#test_file}))
	local sp1=$((26 - (${#USER} * 2)))
	local sp2=$((20 - ${#USER}))
	local sp3=$((17 - ${#USER}))

	test -f "$path" && return ; 
	sp0=$(LIBUNITutils_putspace $sp0)
	sp1=$(LIBUNITutils_putspace $sp1)
	sp2=$(LIBUNITutils_putspace $sp2)
	sp3=$(LIBUNITutils_putspace $sp3)
	mkdir -p "$G_TARGET_DIR/$module/"
    cat > "$path" << EOF
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

#SECTION - main

LIBUNITmain()
{
	LIBUNITutils_setup
	LIBUNITconf_parse
	# LIBUNITsync_backup_files
	LIBUNITcreate_files
	for module in "${!G_MODULES[@]}";do
		echo "$module:	" "${G_MODULES["$module"]}"
	done
}

LIBUNITmain "$@"