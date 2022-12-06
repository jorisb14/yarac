
from "./modules/std.yara" import std std.io std.io.stdout end

module std do
	module io do
		export inline procedure stdout do
			1
		end

		export procedure puts in i64 p64 i64 do
			with length pointer stream as i64 p64 i64 do
				if length 1 less do
					return
				end

				length pointer stream syscall3 drop
			end
		end
	end
end

module program do
	"Hello, World!\n" std.io.stdout std.io.puts
end
