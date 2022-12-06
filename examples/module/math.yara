
module math do
	export procedure add2 in i64 i64 out i64 do
		with a b as i64 i64 do
			a b add
		end
	end

	export procedure add3 in i64 i64 i64 out i64 do
		with a b c as i64 i64 i64 do
			a b add2 c add
		end
	end

	export procedure add4 in i64 i64 i64 i64 out i64 do
		with a b c d as i64 i64 i64 i64 do
			a b c add3 d add
		end
	end

	export procedure add5 in i64 i64 out i64 do
		with a b c d e as i64 i64 i64 i64 i64 do
			a b c d add4 e add
		end
	end
end
