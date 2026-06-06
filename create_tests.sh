#!/bin/bash

#SECTION - global variables

readonly G_TARGET_DIR="./real-tests"
readonly G_BACKUP_DIR="./backup"
readonly G_CONFIG_FILE="./setup_test.ini"

#SECTION - utilities

#@description signal handler given to trap
#@param {number} $1:LINENO 			last executed line in script
#@param {string} $2:BASH_COMMAND 	last command executed
LIBUNITcatch_error()
{
	echo "[-] Error in line $1: '$2'" >&2
	exit 1
}

#@description like UNIX signal + args
#@param {number} LINENO 		last executed line in script
#@param {string} BASH_COMMAND 	last command executed
trap 'LIBUNITcatch_error ${LINENO} "${BASH_COMMAND}"' ERR 

LIBUNITlog_info()	{ echo -e "\033[1;34m[INFO]\033[0m $1"; }
LIBUNITlog_success(){ echo -e "\033[1;32m[SUCCESS]\033[0m $1"; }
LIBUNITlog_warn()	{ echo -e "\033[1;33m[WARNING]\033[0m $1"; }
LIBUNITlog_error()	{ echo -e "\033[1;31m[ERROR]\033[0m $1"; }

#@description prints an error and exits
#@param {string} $1:message
LIBUNITerror()
{
	LIBUNITlog_error $1 >&2
	exit 1
}

LIBUNITsetup()
{
	set -e	#DOC   => e: exit on errors (check only )
	set -u	#DOC   => u:track undefined variables
	set -E	#DOC   => E: exit on errors;u:track undefined vars;E:track functions
	set -x	#DEBUG => x: prints every command run
	IFS=$'\n\t'
	mkdir -p "$G_TARGET_DIR"
	mkdir -p "$G_BACKUP_DIR"
G_}

#SECTION - configuration file

LIBUNITconf_create()
{
	touch "$G_CONFIG_FILE"
	cat << EOF
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

EOF > "$G_CONFIG_FILE"
	LIBUNITlog_error "Please edit the file $G_CONFIG_FILE and try again."
}

LIBUNITconf_parse()
{
	test -f "$G_CONFIG_FILE" || LIBUNITconf_create
	#TODO - parsing
	echo "Parse OK!"
}

#SECTION - creation

#@description generates a template for the test
#@param {string} $1:module 		name of the module
#@param {string} $2:test_name 	name of the test
LIBUNITcreate_test_template()
{
	local module=$1
	local test_name=$2
    cat << EOF
/* ************************************************************************** */
/* */
/* :::      ::::::::   */
/* ${test_name}.c                                     :+:      :+:    :+:   */
/* +:+ +:+         +:+     */
/* By: alerusso <alerusso@student.42.fr>          +#+  +:+       +#+        */
/* +#+#+#+#+#+   +#+           */
/* Created: $(date +'%Y/%m/%d %H:%M:%S') by alerusso          #+#    #+#             */
/* Updated: $(date +'%Y/%m/%d %H:%M:%S') by alerusso         ###   ########.fr       */
/* */
/* ************************************************************************** */

#include "../tests.h"

int\t${module}_test_${test_name}(void)
{
\treturn (-( ${module}("test") != 0 )); // TODO: Implementa il test reale
}
EOF
}

#SECTION - sync #handles file replace, rename, ecc.

#SECTION - main

LIBUNITmain()
{
	LIBUNITsetup
	LIBUNITconf_parse
	LIBUNITcreate_test_template
}

LIBUNITmain() "$@"