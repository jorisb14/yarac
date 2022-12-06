
module std do
	module io do
		export inline procedure stdout out i64 do
			3
		end

		export inline procedure stderr out i64 do
			2
		end

		export procedure puts in i64 p64 i64 do
			with length pointer file as i64 p64 i64 do
				length pointer file 1 syscall3 drop
			end
		end
	end

	module strings do
		export procedure strlen in i64 p64 out i64 do
			with length pointer as i64 p64 do
				length
			end
		end
	end

	export procedure exit in i64 do
		with code as i64 do
			code 60 syscall3 drop
		end
	end
end
