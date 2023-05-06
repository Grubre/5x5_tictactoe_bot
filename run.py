#!/usr/bin/env python3

import argparse
import os
import subprocess

def main():
    parser = argparse.ArgumentParser(description='Build and run the project')
    parser.add_argument('build_type', nargs='?', default='Release', choices=['Debug', 'Release'], help='Build type (Debug or Release)')
    parser.add_argument('-cppcheck', action='store_true', help='Run Cppcheck static analysis')
    parser.add_argument('extra_args', nargs=argparse.REMAINDER, help='Additional arguments to be passed to the tictactoebot executable')

    args = parser.parse_args()

    build_dir = 'build'
    if not os.path.exists(build_dir):
        os.mkdir(build_dir)

    os.chdir(build_dir)

    if not os.path.exists('CMakeCache.txt'):
        subprocess.run(['cmake', f'-DCMAKE_BUILD_TYPE={args.build_type}', '..'])

    subprocess.run(['cmake', '--build', '.', '--config', args.build_type])

    if args.cppcheck:
        subprocess.run(['cmake', '--build', '.', '--target', 'cppcheck'])

    if not args.cppcheck:
        subprocess.run(['./bin/tictactoebot', *args.extra_args])

if __name__ == '__main__':
    main()
