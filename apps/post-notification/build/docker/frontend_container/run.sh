#!/bin/bash

WORKSPACE_NAME="frontend_container"
WORKSPACE_DIR=$(pwd)

usage() { 
	echo "Usage: $0 [-h]" 1>&2
	echo "  Required environment variables:"
	
	if [ -z "${FRONTEND_HTTP_BIND_ADDR+x}" ]; then
		echo "    FRONTEND_HTTP_BIND_ADDR (missing)"
	else
		echo "    FRONTEND_HTTP_BIND_ADDR=$FRONTEND_HTTP_BIND_ADDR"
	fi
	if [ -z "${NOTIFICATION_QUEUE_DIAL_ADDR+x}" ]; then
		echo "    NOTIFICATION_QUEUE_DIAL_ADDR (missing)"
	else
		echo "    NOTIFICATION_QUEUE_DIAL_ADDR=$NOTIFICATION_QUEUE_DIAL_ADDR"
	fi
	if [ -z "${STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR+x}" ]; then
		echo "    STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR (missing)"
	else
		echo "    STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR=$STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR"
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


frontend_proc() {
	cd $WORKSPACE_DIR
	
	if [ -z "${STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR+x}" ]; then
		if ! storage_service_service_thrift_dial_addr; then
			return $?
		fi
	fi

	if [ -z "${NOTIFICATION_QUEUE_DIAL_ADDR+x}" ]; then
		if ! notification_queue_dial_addr; then
			return $?
		fi
	fi

	if [ -z "${FRONTEND_HTTP_BIND_ADDR+x}" ]; then
		if ! frontend_http_bind_addr; then
			return $?
		fi
	fi

	run_frontend_proc() {
		
        cd frontend_proc
        ./frontend_proc --storage_service_service.thrift.dial_addr=$STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR --notification_queue.dial_addr=$NOTIFICATION_QUEUE_DIAL_ADDR --frontend.http.bind_addr=$FRONTEND_HTTP_BIND_ADDR &
        FRONTEND_PROC=$!
        return $?

	}

	if run_frontend_proc; then
		if [ -z "${FRONTEND_PROC+x}" ]; then
			echo "${WORKSPACE_NAME} error starting frontend_proc: function frontend_proc did not set FRONTEND_PROC"
			return 1
		else
			echo "${WORKSPACE_NAME} started frontend_proc"
			return 0
		fi
	else
		exitcode=$?
		echo "${WORKSPACE_NAME} aborting frontend_proc due to exitcode ${exitcode} from frontend_proc"
		return $exitcode
	fi
}


run_all() {
	echo "Running frontend_container"

	# Check that all necessary environment variables are set
	echo "Required environment variables:"
	missing_vars=0
	if [ -z "${FRONTEND_HTTP_BIND_ADDR+x}" ]; then
		echo "  FRONTEND_HTTP_BIND_ADDR (missing)"
		missing_vars=$((missing_vars+1))
	else
		echo "  FRONTEND_HTTP_BIND_ADDR=$FRONTEND_HTTP_BIND_ADDR"
	fi
	
	if [ -z "${NOTIFICATION_QUEUE_DIAL_ADDR+x}" ]; then
		echo "  NOTIFICATION_QUEUE_DIAL_ADDR (missing)"
		missing_vars=$((missing_vars+1))
	else
		echo "  NOTIFICATION_QUEUE_DIAL_ADDR=$NOTIFICATION_QUEUE_DIAL_ADDR"
	fi
	
	if [ -z "${STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR+x}" ]; then
		echo "  STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR (missing)"
		missing_vars=$((missing_vars+1))
	else
		echo "  STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR=$STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR"
	fi
		

	if [ "$missing_vars" -gt 0 ]; then
		echo "Aborting due to missing environment variables"
		return 1
	fi

	frontend_proc
	
	wait
}

run_all
