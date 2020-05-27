import csv
my_reader = csv.reader(open('interviews1.csv'))
kylectr = 0
chrisctr = 0
trevorctr = 0
davidctr = 0
for record in my_reader:
    if record[3] == 'Kyle Burton':
        kylectr += 1
    if record[3] == 'Christopher Hilbert':
        chrisctr += 1
    if record[3] == 'Trevor Umeda':
        trevorctr += 1
    if record[3] == 'David Kim':
        davidctr += 1
print("Kyle Burton: %i" % (kylectr))
print("Chris Hilbert: %i" % (chrisctr))
print("Trevor Umeda: %i" % (trevorctr))
print("David Kim: %i" % (davidctr))
