
from "./modules/std.yara" import
	std
	std.io
end

module test do
	10 drop 1 1 equal drop
end

10 drop 1 1 equal drop
1 if clone 1 equal do
	69
end
1 if clone 1 equal do
	69
	0 if clone 1 equal do
		69
	end
end
420
1 while clone 10 less do
	666 drop
	1 add
end
1 while clone 10 less do
	666 drop
	1 add
	1 while clone 10 less do
		666 drop
		1 add
	end
end
1 while clone 10 less do
	666 drop
	1 add
	0 if clone 1 equal do
		69
	end
end
0 if clone 1 equal do
	69
	1 while clone 10 less do
		666 drop
		1 add
	end
end
0 if clone 1 equal do
	69
	1 while clone 10 less do
		666 drop
		1 add
		0 if clone 1 equal do
			69
		end
	end
end
0 if clone 1 equal do
	5
	0 if clone 1 equal do
		5
	end
	0 if clone 1 equal do
		5
	end
	0 if clone 1 equal do
		5
	end
	0 if clone 1 equal do
		5
		0 if clone 1 equal do
			5
			if 2 do
				if 8 do
					66666
				end
			end
		end
	end
end
2

with a b c as i64 i64 i64 do
	10 a add drop
	20 b add drop
	30 c add drop
end

module test2 do
	10 drop 1 1 equal drop

	1 while clone 10 less do
		666 drop
		1 add
		0 if clone 1 equal do
			69
		end
	end
	0 if clone 1 equal do
		69
		1 while clone 10 less do
			666 drop
			1 add
		end
	end
end

# 
# module mod1 do
# 	module mod2 do
# 		procedure func1 do end
# 		procedure func2 do end
# 	end
# 
# 	procedure func3 do end
# 	procedure func4 do end
# 
# 	procedure func5 do
# 		module mod3 do # should be an error
# 		end
# 	end
# 
# 	procedure func6 do
# 		module mod4 do # should be an error
# 		end
# 	end
# 
# 	module mod5 do
# 		procedure func7 do end
# 
# 		procedure func8 do
# 			module mod6 do # should be an error
# 				procedure func9 do end
# 				procedure func10 do
# 					procedure func11 do end
# 				end
# 			end
# 		end
# 	end
# end
# 
