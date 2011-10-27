requestPath="../../src/request/"
for filename in $(find $requestPath -name '*.cpp')
do
	echo "filename:"$filename
	newfilename=$(grep -m 1 '^J.*::' $filename | sed 's#\(^J.*\)::.*$#\1#g')
	echo "newfilename:"$newfilename
	strInclude=$(echo $filename | sed 's#cpp#h#g')
	echo "strInclude:"$strInclude
	echo '#include "'$strInclude'"' >$newfilename
done
#find $requestPath -name '*.cpp' -exec grep -m 1 '^J.*::' {} \;| sed 's#\(^J.*\)::.*$#\1#g'
