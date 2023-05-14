# Tự học OpenGL

  Setup / Cài đặt:
- cmake.org/download/ --> Nếu sử dụng Windows thì chọn Windows win64-x64 Installer với version mới nhất
- glfw.org/download.html --> Nhấn vào Source package --> giải nén nó, tạo thư mục mới trong nó, đặt tên là build
- glad.dav1d.de --> Ở mục API: chọn gl: Version 3.3, Profile: Core --> Nhấn vào Generate --> Chọn glad.zip vào giải nén nó
- Tạo project: Empty Project, ngôn ngữ C++
- Vào địa chỉ thư mục project đã tạo, tạo thư mục mới tên Libraries, trong Libraries tạo 2 thư mục mới tên lib, include
- Mở cmake installer, ở Where is the source code: chọn thư mục glfw đã giải nén, ở Where is the build the binaries: chọn thư mục glfw/build
--> Nhấn Configure, ở Specify the generator for this project: chọn IDE mình sử dụng --> Nhấn Finish --> Nhấn Configure --> Nhấn Generate
- Vào glfw/build mở GLFW.sln, chuột phải vào solution chọn Build solution
- Vào glfw/build/src/Debug sao chép glfw3.lib vào <Project đã tạo>/Libraries/lib
- Vào glfw/include sao chép thư mục GLFW vào <Project đã tạo>/Libraries/include
- Vào glad/include sao chép thư mục glad và KHR vào <Project đã tạo>/Libraries/include
- Vào glad/src sao chép glad.c vào thư mục chứa <Project đã tạo>.sln
- Vào Project đã tạo, chọn "Project" trên cùng --> Properties --> Platforms: All platforms --> VC++ Directories --> Include Directories: <Edit...>
--> Thêm thư mục Libraries/include --> Chọn OK --> Library Directories: <Edit...> --> Thêm thư mục Libraries/lib --> Chọn OK
--> Linker: Input: <Edit...> --> Nhập glfw3.lib <Enter> opengl32.lib --> Chọn OK
- Sao chép glad.c vào thư mục Source Files, nơi mà tạo các file .cpp
