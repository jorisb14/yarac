
module program do
	const stdout as u8 do 1u end

	export procedure main in i64 p64 out i64 do
		with argc argv as u64 p64 do
			switch argc do
				case 1i do
					35u "Only one cmd argument is provided!\n\0" stdout syscall3 drop
				break end

				case 2i do
					35u "Only two cmd arguments are provided!\n\0" stdout syscall3 drop
				break end

				default do
					37u "Provided more than 2 cmd arguments!\n\0" stdout syscall3 drop
				break end
			end
		end

		0i return
	end
end

