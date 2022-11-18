with open('lab1.txt', "r+") as f:
    lines = f.readlines()
    new = []
    i = 1
    for line in lines:
        if line[0:9] == 'Checking ':
            pass
        elif line[0] == '{0}/'.format(i):
            i = i + 1
            pass
        else:
            new.append(line)
    print(new)
    for l in new:
        f.write("%s\n" % l)
