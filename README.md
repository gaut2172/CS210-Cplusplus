# Summarize the project and what problem it was solving.
This is a zoo program that lets a user add, remove, and save animals to the zoo database.
This is my first multiclass project. This is a C++ program that incorporates Java for certain functionalities.
The prompt required the use of a vector to keep track of the animals added. I needed to allow C++ inheritance.

# What did you do particularly well?
I believe I did well with exception handling and input validation. I spent a lot of time thinking of outlier inputs that could cause problems and I accounted for them.

# Where could you enhance your code? How would these improvements make your code more efficient, secure, and so on?
Being the first time I wrote a multiclass object oriented program, my project definitely functions. With that said, I believe there are some problems with the organization of class members, and how the inheritance works. I had trouble finding a way to use a vector that needs access to base and derived class members. My solution was to use a vector of pointers (of the base class), and put most of the class members in the base class.

# Did you find writing any piece of this code challenging, and how did you overcome this? What tools and/or resources are you adding to your support network?
Because the prompt required the use of one vector to traverse the base class and derived classes, I chose to use pointers-- which was quite challenging. At the moment I am still learning when it comes to pointer usage and memory allocation and deallocation.
I gravitated towards StackOverflow and GeeksforGeeks whenever I needed to research.

# What skills from this project will be particularly transferable to other projects and/or course work?
Understanding how C++ class hierarchy works, along with its polymorphism and inheritance will help me to code better-organized OO projects in the future. This was my first legitimate multiclass OO program, and overall I learned a lot about class design. Throughout it I gained debugging skills as well, and writing it in C++ helped me learn memory leak and allocation concepts too.

# How did you make this program maintainable, readable, and adaptable?
I followed the university's code writing best practices to make sure the project was readable.
I separated program tasks into clearly defined and organized functions so that the project is easy to update and maintain. The code allows the user to input anything and should still work.
