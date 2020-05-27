#! python3
# mclip.py - A multi-clipboard program.
import pyperclip

TEXT = {'agree': """agreed, sounds vv good""",
        'rave': """:crabrave: :crabrave: :crabrave: :crabrave: :crabrave: :crabrave: :crabrave: :crabrave:""",
        'capoo': """:capoonod: :capoonod: :capoonod: :capoonod: :capoonod: :capoonod:""",
        'concur': """doctor do you concur?"""}

import sys
if len(sys.argv) < 2:
    print('Usage: python mclip.py [keyphrase] - copy phrase text')
    sys.exit()

keyphrase = sys.argv[1]    # first command line arg is the keyphrase

if keyphrase in TEXT:
    pyperclip.copy(TEXT[keyphrase])
    print('Text for ' + keyphrase + ' copied to clipboard.')
else:
    print('There is no text for ' + keyphrase)
