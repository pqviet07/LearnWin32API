
#!/bin/bash
#author: Phung Quoc Viet
#description: read all line from filname then create directorys with format: line/no.line
filename="filename"
n=1
while read line; do
    # reading each line
    mkdir "$n. $line"
    touch "./$n. $line/$line.cpp"
    echo -n "File No.$n: $line"
    echo "... Created"
    n=$((n + 1))

done <$filename
read -p "Press Enter to continue"