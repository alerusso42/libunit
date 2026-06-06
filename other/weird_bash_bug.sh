#!/bin/bash

#SECTION - global variables

readonly G_TARGET_DIR="./real-tests"
readonly G_BACKUP_DIR="./backup"
readonly G_CONFIG_FILE="./setup_test.ini"

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
	LIBUNITlog_error $1 >&2
	exit 1
}

LIBUNITsetup()
{
	set -e		#DOC	=> e: exit on errors (check only )
	set -u		#DOC	=> u:track undefined variables
	set -E		#DOC	=> E:track functions
	set -x		#DEBUG	=> x: prints every command run
	mkdir -p "$G_TARGET_DIR"
	mkdir -p "$G_BACKUP_DIR"
	#DOC	=> trap is like UNIX signal with argument handling
	#DOC	=> LINENO:last executed line in script
	#DOC	=> BASH_COMMAND: last command executed
	trap 'LIBUNITcatch_error ${LINENO} "${BASH_COMMAND}"' ERR 
}

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

int	${module}_test_${test_name}(void)
{
	return (-( ${module}("test") != 0 )); // TODO: Implementa il test reale
}
EOF
}

#SECTION - sync #handles file replace, rename, ecc.

#SECTION - main

LIBUNITmain()
{
	LIBUNITconf_parse
	exit 1
	LIBUNITsetup
	LIBUNITcreate_test_template
}

LIBUNITmain "$@"

#FIXME - dopo ore di debug:
#linea 68 deve diventare da:
#68 - EOF > "$G_CONFIG_FILE"
#a:
#68 - EOF
#69 -  > "$G_CONFIG_FILE"