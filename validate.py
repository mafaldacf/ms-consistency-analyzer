#!/usr/bin/env python3
import argparse
import yaml
import os
import glob
from colorama import Fore, Style, init

apps = ['postnotification', 'postnotification_simple', 'shopping_app']
detection_modes = ['foreign_keys_default']

expected_output = {
    'foreign_keys_default': {
        'postnotification': {
            'uploadservice.uploadpost': 2,
        },
        'postnotification_simple': {
            'uploadservice.uploadpost': 1,
        },
        'shopping_app': {
            'frontend.checkout': 1,
        },
    },
}

expected_output_details = {
    'foreign_keys_default': {
        'postnotification': {
            'uploadservice.uploadpost': [
                {
                    'read': '(0, 8) read(posts_db, query, result) @ StorageService',
                    'write': '(0, 2) write(posts_db, post, post) @ StorageService',
                },
                {
                    'read': '(0, 9) read(analytics_db, query, result) @ AnalyticsService',
                    'write': '(0, 5) write(analytics_db, analytics, analytics) @ AnalyticsService',
                },
            ],
        },
        'postnotification_simple': {
            'uploadservice.uploadpost': [
                {
                    'read': '(0, 3) read(posts_db, query, result) @ StorageService',
                    'write': '(0, 0) write(posts_db, post, post) @ StorageService',
                }
            ],
        },
        'shopping_app': {
            'frontend.checkout': [
                {
                    'read': '(0, 11) read(order_db, query, result) @ OrderService',
                    'write': '(0, 0) write(order_db, order, order) @ OrderService',
                }
            ],
        },
    },
}

# requests flagged with wrong output
flagged_requests = {
    'foreign_keys_default': {
        'postnotification': {},
        'postnotification_simple': {},
        'shopping_app': {},
    },
}
flagged_requests_details = {
    'foreign_keys_default': {
        'postnotification': {},
        'postnotification_simple': {},
        'shopping_app': {},
    },
}

def get_request_typename(filename):
    return filename.split('_foreign_keys_default.yaml')[0].replace('_', '.')

def get_request_tag(filename):
    return '[' + get_request_typename(filename) + ']'

def get_max_len_request_tags(files):
    max_len = 0
    for file in files:
        request_tag = get_request_tag(os.path.basename(file))
        if len(request_tag) > max_len:
            max_len = len(request_tag)
    return max_len

def get_padding_title(title):
    return (40 - len(title)//2) * '='


def get_padding_details(max_len_request_tags, len_request_tag):
    return (max_len_request_tags - len_request_tag) * ' '

def validate(app, detection_mode):
    base_path = f'output/{app}/detection/'
    pattern = os.path.join(base_path, f'*_{detection_mode}.yaml')
    files = glob.glob(pattern)

    for file in files:
        filebasename = os.path.basename(file)
        request_typename = get_request_typename(filebasename)
        with open(file, 'r') as f:
            data = yaml.safe_load(f)

        current_number = data.get('number_inconsistencies', 0)

        expected_number = expected_output[detection_mode][app].get(request_typename, 0)
        if current_number != expected_number:
            flagged_requests[detection_mode][app][request_typename] = current_number
            flagged_requests_details[detection_mode][app][request_typename] = data.get('xcy_inconsistencies', [])

def summary(app, detection_mode):
    if len(flagged_requests[detection_mode][app]) == 0:
        print(f"[{app.upper()}] OK!")
        return
    
    print(f"[{app.upper()}] FAILED...")

    for flagged_request in flagged_requests[detection_mode][app]:
        current_number = flagged_requests[detection_mode][app].get(flagged_request, 0)
        expected_number = expected_output[detection_mode][app].get(flagged_request, 0)
        if current_number != expected_number:
            prefix = f"{Fore.LIGHTRED_EX}[{flagged_request}]{Style.RESET_ALL}"
            print(f"{prefix} current: {current_number}, expected: {expected_number}")

            current_details = flagged_requests_details[detection_mode][app][flagged_request]
            expected_details = expected_output_details[detection_mode][app][flagged_request]
            for inconsistency in current_details:
                if inconsistency in expected_details:
                    print(f"\t- {Fore.LIGHTGREEN_EX}(OK){Style.RESET_ALL} {inconsistency['read']}")
                else:
                    print(f"\t- {Fore.LIGHTBLUE_EX}(EXTRA){Style.RESET_ALL} {inconsistency['read']}")
            
            for expected_inconsistency in expected_details:
                if expected_inconsistency not in current_details:
                    print(f"\t- {Fore.LIGHTRED_EX}(MISSING){Style.RESET_ALL} {expected_inconsistency['read']}")

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="Visualize graphs based on the specified application and graph type")
    parser.add_argument('--app', '-a', choices=apps, help="The application for which to visualize the graph")
    parser.add_argument('--all', action='store_true', help="Construct all combinations of digraphs for all applications")
    args = parser.parse_args()

    if args.all == False and args.app == None:
        print(f"[ERROR] invalid arguments!")
        exit(-1)

    if args.app != None:
        apps = [args.app]
    
    for detection_mode in detection_modes:
        padding_title = get_padding_title(detection_mode)
        print(f"\n{padding_title} {detection_mode.upper()} {padding_title}\n")
        for app in apps:
            validate(app, detection_mode)
            summary(app, detection_mode)
            print()
    