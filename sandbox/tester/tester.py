
#!/usr/bin/env python3

# Modules and libraries
import os
import argparse
import subprocess
import shlex


class Style():
	BLACK = '\033[30m'
	RED = '\033[31m'
	GREEN = '\033[32m'
	YELLOW = '\033[33m'
	BLUE = '\033[34m'
	MAGENTA = '\033[35m'
	CYAN = '\033[36m'
	WHITE = '\033[37m'
	UNDERLINE = '\033[4m'
	RESET = '\033[0m'


# Parsing command line arguments
parser = argparse.ArgumentParser()

parser.add_argument(
	'--settings',
	action='store',
	type=str,
	required=True,
	help='settings for the tester')

options = vars(parser.parse_args())


# Validating settings flag
settings_file_path = options['settings']

if not os.path.isfile(settings_file_path):
	print('Invalid file passed as `--settings` flag!')
	parser.print_help()
	exit(1)

if not settings_file_path.endswith('.json'):
	print('Settings file must be .json file!')
	parser.print_help()
	exit(1)


# Reading settings
import json

with open(settings_file_path, 'r') as settings_file:
	settings = json.load(settings_file)


# Performing tests
passed = 0
failed = 0
aborted = 0

for test in settings:
	name = test['name']
	compared = test['compared']
	exclude = test['exclude']
	debug = test['debug']

	if exclude:
		continue

	cleanup = test['cleanup']
	for step in cleanup:
		res = subprocess.run(step, shell=True)

		if debug:
			print(res)
			input('Press enter to continue...')

	print('+----------------------------------------+')
	print(f'Testing {name}:')

	run = test['run']
	for step in run:
		res = subprocess.run(step, shell=True, stderr=subprocess.DEVNULL)

		if debug:
			print(res)
			input('Press enter to continue...')

		if res.returncode != 0:
			print('Subprocess finished with non-zero exit code')
			print(Style.BLUE + ' Aborted' + Style.RESET)
			aborted += 1
			continue

	if os.path.isfile(compared):
		with open(compared, 'r') as file:
			if len(file.read()) <= 0:
				print(Style.GREEN + ' Passed' + Style.RESET)
				passed += 1
			else:
				print(Style.RED + ' Failed' + Style.RESET)
				failed += 1
	else:
		print(f'Failed to find file {compared}')
		print(Style.BLUE + ' Aborted' + Style.RESET)
		aborted += 1

	cleanup = test['cleanup']
	for step in cleanup:
		res = subprocess.run(step, shell=True)
		if debug:
			print(res)
			input('Press enter to continue...')

print('+----------------------------------------+')
print('Results:')
print(' ' + Style.GREEN + f'{passed}' + ' tests passed' + Style.RESET + ', ' + Style.RED + f'{failed}' + ' tests failed' + Style.RESET + ', and ' + Style.BLUE + f'{aborted} tests aborted' + Style.RESET)
