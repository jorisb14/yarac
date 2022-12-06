
module logging do
	export procedure log in i64 p64 i64 do
		inline procedure wrapper in i64 p64 i64 do
			with length pointer file as i64 p64 i64 do
				length pointer file 1 syscall3
			end

			if clone 0 nequal do
				1 60 syscall1 drop # Kill if non-zero code was returned by syscall3
			end
		end

		with length pointer file as i64 p64 i64 do
			length pointer file wrapper
		end
	end
end
