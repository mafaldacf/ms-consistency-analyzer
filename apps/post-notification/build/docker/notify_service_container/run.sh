#!/bin/bash

WORKSPACE_NAME="notify_service_container"
WORKSPACE_DIR=$(pwd)

usage() { 
	echo "Usage: $0 [-h]" 1>&2
	echo "  Required environment variables:"
	
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


notify_service_proc() {
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

	run_notify_service_proc() {
		
        cd notify_service_proc
        ./notify_service_proc --storage_service_service.thrift.dial_addr=$STORAGE_SERVICE_SERVICE_THRIFT_DIAL_ADDR --notification_queue.dial_addr=$NOTIFICATION_QUEUE_DIAL_ADDR &
        NOTIFY_SERVICE_PROC=$!
        return $?

	}

	if run_notify_service_proc; then
		if [ -z "${NOTIFY_SERVICE_PROC+x}" ]; then
			echo "${WORKSPACE_NAME} error starting notify_service_proc: function notify_service_proc did not set NOTIFY_SERVICE_PROC"
			return 1
		else
			echo "${WORKSPACE_NAME} started notify_service_proc"
			return 0
		fi
	else
		exitcode=$?
		echo "${WORKSPACE_NAME} aborting notify_service_proc due to exitcode ${exitcode} from notify_service_proc"
		return $exitcode
	fi
}


run_all() {
	echo "Running notify_service_container"

	# Check that all necessary environment variables are set
	echo "Required environment variables:"
	missing_vars=0
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

	notify_service_proc
	
	wait
}

run_all
