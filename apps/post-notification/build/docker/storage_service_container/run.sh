#!/bin/bash

WORKSPACE_NAME="storage_service_container"
WORKSPACE_DIR=$(pwd)

usage() { 
	echo "Usage: $0 [-h]" 1>&2
	echo "  Required environment variables:"
	
	if [ -z "${POST_DB_DIAL_ADDR+x}" ]; then
		echo "    POST_DB_DIAL_ADDR (missing)"
	else
		echo "    POST_DB_DIAL_ADDR=$POST_DB_DIAL_ADDR"
	fi
	if [ -z "${STORAGE_SERVICE_SERVICE_THRIFT_BIND_ADDR+x}" ]; then
		echo "    STORAGE_SERVICE_SERVICE_THRIFT_BIND_ADDR (missing)"
	else
		echo "    STORAGE_SERVICE_SERVICE_THRIFT_BIND_ADDR=$STORAGE_SERVICE_SERVICE_THRIFT_BIND_ADDR"
	fi
		
	exit 1; 
}

while getopts "h" flag; do
	case $flag in
		*)
		usage
		;;
	esac
done


storage_service_proc() {
	cd $WORKSPACE_DIR
	
	if [ -z "${POST_DB_DIAL_ADDR+x}" ]; then
		if ! post_db_dial_addr; then
			return $?
		fi
	fi

	if [ -z "${STORAGE_SERVICE_SERVICE_THRIFT_BIND_ADDR+x}" ]; then
		if ! storage_service_service_thrift_bind_addr; then
			return $?
		fi
	fi

	run_storage_service_proc() {
		
        cd storage_service_proc
        ./storage_service_proc --post_db.dial_addr=$POST_DB_DIAL_ADDR --storage_service_service.thrift.bind_addr=$STORAGE_SERVICE_SERVICE_THRIFT_BIND_ADDR &
        STORAGE_SERVICE_PROC=$!
        return $?

	}

	if run_storage_service_proc; then
		if [ -z "${STORAGE_SERVICE_PROC+x}" ]; then
			echo "${WORKSPACE_NAME} error starting storage_service_proc: function storage_service_proc did not set STORAGE_SERVICE_PROC"
			return 1
		else
			echo "${WORKSPACE_NAME} started storage_service_proc"
			return 0
		fi
	else
		exitcode=$?
		echo "${WORKSPACE_NAME} aborting storage_service_proc due to exitcode ${exitcode} from storage_service_proc"
		return $exitcode
	fi
}


run_all() {
	echo "Running storage_service_container"

	# Check that all necessary environment variables are set
	echo "Required environment variables:"
	missing_vars=0
	if [ -z "${POST_DB_DIAL_ADDR+x}" ]; then
		echo "  POST_DB_DIAL_ADDR (missing)"
		missing_vars=$((missing_vars+1))
	else
		echo "  POST_DB_DIAL_ADDR=$POST_DB_DIAL_ADDR"
	fi
	
	if [ -z "${STORAGE_SERVICE_SERVICE_THRIFT_BIND_ADDR+x}" ]; then
		echo "  STORAGE_SERVICE_SERVICE_THRIFT_BIND_ADDR (missing)"
		missing_vars=$((missing_vars+1))
	else
		echo "  STORAGE_SERVICE_SERVICE_THRIFT_BIND_ADDR=$STORAGE_SERVICE_SERVICE_THRIFT_BIND_ADDR"
	fi
		

	if [ "$missing_vars" -gt 0 ]; then
		echo "Aborting due to missing environment variables"
		return 1
	fi

	storage_service_proc
	
	wait
}

run_all
