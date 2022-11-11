import os

def parser():
    with open("lab1.txt", "r") as f:
        lines = f.readlines()
        if lines == "":
            return True
        else:
            return False

name = 'log'
value = parser()

with open(os.environ['GITHUB_OUTPUT'], 'a') as fh:
    print(f'{name}={value}', file=fh)
