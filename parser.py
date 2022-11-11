def parser():
    with open("lab1.txt", "r") as f:
        lines = f.readlines()
        if lines == "":
            return True
        else:
            return False

parser()
