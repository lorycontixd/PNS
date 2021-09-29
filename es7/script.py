import subprocess
import sys, os
import argparse

states = [
    "solid",
    "liquid",
    "gas"
]

ap = argparse.ArgumentParser()
ap.add_argument(
    "--clear",
    action="store_true"
)
args = ap.parse_args()

if args.clear:
    print("Clearing all previous outputs...")
    os.system("chmod +x clean.sh && ./clean.sh")

for i1, state in enumerate(states):
    cmd = f"make && ./main inputs/{state}.ini"
    print("Running command:\t",cmd)
    os.system(cmd)


