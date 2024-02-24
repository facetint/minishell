echo "Compiling for tester mode..."
gcc -DTESTER_MODE=1 aborter.c allocator.c tester.c -o allocator_test

if [ $? -ne 0 ]; then
	echo "Compilation failed."
	exit 1
fi

echo "Compilation successful. Brute force testing starting..."
echo "----- MALLOC  <-->  FREE -----"
for ((i=1; i<=10000; i++))
do
	./allocator_test > output.txt

	if [ $? -ne 0 ]; then
		echo "Execution failed."
		exit 1
	fi

	malloc_count=$(grep 'MALLOC' output.txt | grep -v '0x0' | wc -l | awk '{print $1}')
	free_count=$(grep 'FREE' output.txt | wc -l | awk '{print $1}')

	echo "$i# test: $malloc_count <--> $free_count"
	if [ $malloc_count -ne $free_count ]; then
		echo "Counts of 'MALLOC' and 'FREE' are not equal."
		exit 1
	fi
done

echo "All tests passed successfully."