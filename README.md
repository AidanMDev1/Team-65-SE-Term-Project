QuestClock Installation Guide
=============================

Prerequisites
-------------

Before you begin, make sure your system meets the following prerequisites:

*   C++ compiler that supports C++17 standards.
*   SFML library for graphics and multimedia.
*   libcurl library for making HTTP requests.
*   It's recommended to use MongoDB to run the database alongside the software.
*   Node.js for server-side JavaScript.
*   Express framework for building web applications.
*   Mongoose library for MongoDB object modeling.
*   Nodemon for automatic server restarts during development.

Installation Steps
------------------

### 1\. Install C++ Compiler

Depending on your operating system, you may need to install a C++ compiler that supports C++17. Refer to your system's documentation or use the package manager to install the appropriate compiler (some ones used were CLion and VSCode).

### 2\. Install SFML Library

Follow the instructions on the SFML website to download and install the SFML library for your operating system.


Install the other required tools and libraries through command line in your project directory

npm install express 

npm install mongoose

npm install nodemon

npm install body-parser

npm install bycrypt (might use later for password encryption)

watch https://www.youtube.com/watch?v=H1naJEHsxbQ to set up libcurl, before trying to run the makefiles make sure to add CURL_ROOT in ENVIRONMENT VARIABLES with the path to your CURL directory (ex. C:/DEV/CURL) as the value

watch this video if you want to better understand the server.js code https://www.youtube.com/watch?v=_7UQPve99r4&t=3196s


Running QuestClock
------------------

After installing all the prerequisites, you can now run QuestClock. Follow these steps:

1.  Clone the QuestClock repository from GitHub.
    
2.  Navigate to the project directory.
    
3.  Run the following command to install dependencies

4.  Start the server from MongoDB
