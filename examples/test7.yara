
from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end


from "./modules/std.yara" import
	std.io.stdout
	std.io.putp64
	std.io.puti64
end

0u
-128i
6.4f
5f

module program do
	export alias bool as u8 end
	export const true as u8 do 1u end
	export const false as u8 do 0u end

	export const pi as f32 do
		3.14f
	end

	const G as f32 do
		pi 10i multiply 3i add
	end

	export struct Vec3i do
		field x as f32 end
		field y as f32 end
		const count as u8 do 2u end
	end

	struct Point do
		field a as i64 end
		field b as i32 end
	end

	export packed struct Color do
		field r as u8 end
		field g as u8 end
		field b as u8 end
		field a as u8 end
		const count as u8 do 4u end
	end

	module utils do
		export procedure swrite in i64 p64 i64 do
			with len ptr fd as i64 p64 i64 do
				if len 0i less do
					return
				end

				if ptr 0i equal do
					return
				end

				if ptr 0i equal do
					return
				end

				len ptr df syscall3 drop
			end
		end
	end

	procedure structTest do
		packed struct Vec2f do
			field x as f32 end
			field y as f32 end
		end

		1f 0f with v as Vec2f do
			v.x
			v.y
		end
	end

	procedure at in p64 u64 do
		with p i do
			p i add read64 puti64
			p i add 654321i write64
		end
	end

	procedure arrayTest do
		const N as u32 do
			69u
		end

		bytes N xs end
		xs 420u write64
		xs read64 putu64

		4u with a as i16 do
			a puti16
		end

		xs
		with p as p64 do
		end

		alias int32 as bytes 4u end
		int32 var1 end
		int32 var2 end
	end

	export procedure main in i64 p64 out i64 do
		drop drop
		"Hello, World!\n" stdout putp64
		"Hello, World!\n" stdout utils.swrite

		0i while clone 10i less do
			clone std.io.puti64
			1i add
		end drop

		0i return
	end
end
