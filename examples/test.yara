
module program do
	procedure func1 in i64 i64 i64 i64 i64 i64 i64 i64 i64 i64 i64 i64 i64 i64 i64 i64 i64 i64 i64 i64
		i64 i64 i64 i64 i64 i64 i64 i64 i64 i64
	do
		drop drop drop drop drop drop drop drop drop drop drop drop drop drop drop drop drop drop drop
		drop drop drop drop drop drop drop drop drop drop drop
	end

	export procedure main in p64 i64 out i64 do
		drop drop
		test
		0
	end

	export inline procedure test do
		"Hello, Test!\n" 1 1 syscall3 drop
	end
end
