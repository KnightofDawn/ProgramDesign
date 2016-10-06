import string
import re
pos_split = re.compile("[\u4E00-\uFFFF]+/([a-zA-Z]+)")
orig_file = open("tagged_data.txt","r")
seg_flie = open("hidden_state.txt","w")
S = set();
for line in orig_file:
    line = line.strip()
    pos = re.findall(pos_split,line)
    for word in pos:
        S.add(word)
cnt = 0
for part in S:
    seg_flie.writelines(part + ' ' + str(cnt) + '\n')
    cnt += 1
orig_file.close()
seg_flie.close()
