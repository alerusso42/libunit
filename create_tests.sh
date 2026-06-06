#!/bin/bash

#SECTION - global variables

readonly G_TARGET_DIR="./real-tests"
readonly G_BACKUP_DIR="./backup"
readonly G_CONFIG_FILE="./setup_test.ini"
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
	LIBUNITlog_error "line "$1": '$2'" >&2
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
	# set -x		#DEBUG	=> x: prints every command run
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
	local str=""

	(($1 < 0)) && $1=0
	for ((i = 0; i != $1; i++)); do
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

	set +u	#DOC	=>	deactivates undefined variable check
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
	str="$1"
	str="${str:$from:$to}"
	set -u
	echo "$str"
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
		if test "$line" = "" || test $start = ";" || test $start = "["; then
			continue;
		elif test -n "$mod_name" && test $start = "#";then
			LIBUNITerror "conf_parse, line $counter:unclosed module $mod_name"
		elif test $start = "#";then	#DOC	=> create new test module
			mod_name=$(LIBUNITutils_strtrim "$line" 1)
		elif test $start = "]";then	#DOC	=> close current test module
			G_MODULES["$mod_name"]="$tests"
			mod_name=""
			tests=""
		elif test "$mod_name" = "";then
			LIBUNITerror "conf_parse, line $counter:undefined module"
		else	#DOC	=> push to current test array
			tests="$tests $line"
		fi
	done < "$G_CONFIG_FILE"
	echo "Parse OK!"
	# set +x
}

#SECTION - creation

#@description generates a template for the test
#@param {string} $1:module 		name of the module
#@param {string} $2:test_name 	name of the test
LIBUNITcreate_test_template()
{
	local module=$1
	local test_name="$2"
	local test_file="$2.c"
	local sp0=$((51 - ${#test_file}))
	local sp1=$((26 - (${#USER} * 2)))
	local sp2=$((20 - ${#USER}))
	local sp3=$((17 - ${#USER}))
	sp0=$(LIBUNITutils_putspace $sp0)
	sp1=$(LIBUNITutils_putspace $sp1)
	sp2=$(LIBUNITutils_putspace $sp2)
	sp3=$(LIBUNITutils_putspace $sp3)
	echo "$sp1"
	echo "$sp2"
	echo "$sp3"
	mkdir -p "$G_TARGET_DIR/$module/"
    cat > "$G_TARGET_DIR/$module/01_$test_file" << EOF
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

int	${module}_test_${test_name}(void)
{
	return (-(${module}() != 0 ));
}
EOF
}

#SECTION - sync #handles file replace, rename, ecc.

#SECTION - main

LIBUNITmain()
{
	LIBUNITutils_setup
	LIBUNITconf_parse
	LIBUNITcreate_test_template mod test
	for module in "${!G_MODULES[@]}";do
		echo "$module:	" ${G_MODULES["$module"]}
	done
}

LIBUNITmain "$@"