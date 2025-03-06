# CS50x (2023) - Introduction to Computer Science

<img src="https://github.com/user-attachments/assets/7cf6465c-dd18-471d-b403-41bf084e8341" width="500">

## Certificate obtained

🔗 [Verify my certificate](https://cs50.harvard.edu/certificates/25f74edd-79df-4ae1-bcd0-5a0180d473ab)

![Course Completed](https://img.shields.io/badge/Completed-✅-brightgreen)  
📌 **Harvard University's CS50x - Intro to Computer Science**  

## ▌ Description
CS50x is Harvard's renowned introduction to **computer science and programming**. The course covers fundamental concepts such as **algorithms, data structures, memory management, and web development**, using **C, Python, SQL, JavaScript, HTML, and CSS**.  

Through hands-on problem sets and projects, students develop strong problem-solving skills and computational thinking.

## ▌ Objectives
▸ Learn **programming fundamentals** through C and Python  
▸ Understand **memory management** and **data structures** (arrays, linked lists, hash tables, trees)  
▸ Implement **sorting and searching algorithms**  
▸ Work with **SQL databases** and **web programming**  
▸ Develop a final project applying all acquired skills  

## ▌ Completed Projects & Problem Sets
### ■ **Core Problem Sets**
| Topic | Concepts Covered |
|------------------|----------------|
| **C Basics** | Variables, loops, conditionals, functions |
| **Arrays & Strings** | String manipulation, pointers |
| **Algorithms** | Sorting (selection, bubble, merge, quick), recursion |
| **Memory Management** | Dynamic allocation, linked lists, hash tables, trees |
| **Data Structures** | Queues, stacks, dictionaries, tries |
| **Python & SQL** | Object-oriented programming, database queries |
| **Web Development** | Flask, HTML, CSS, JavaScript |

## ▌ Final Project: MyRecipes Web Application

<img src="https://github.com/user-attachments/assets/a49604b2-799d-44a6-ba20-acb17432c701" width="500">

📽 **Video Demo:** [Watch on YouTube](https://youtu.be/c2erWba9aRU)  

### ■ Project Overview
MyRecipes is a web application designed to allow users to **create, share, and discover culinary recipes**. It provides a user-friendly platform where people can explore a variety of dishes without the need for prior registration.  

This project was developed in collaboration with **Diego Agudelo** and **Ralph Balazs**, both students at **42 School Paris**.

### ■ Features
✔ **User-friendly recipe management**: Users can easily modify their recipes while retaining original data.  
✔ **Categorization**: Recipes are classified into three main categories:
   - **Culinary Arts**: Main dishes and starters  
   - **Bakery**: Bread and baked goods  
   - **Pastry**: Desserts and sweet treats  
✔ **Admin Panel**:  
   - Manage user accounts (**Admin login**: admin | **Password**: 12345)  
✔ **Security Measures**:  
   - Password encryption for user safety  
   - Password recovery system based on first and last name  
   - Profile customization  

### ■ Demo Credentials  
To test the application, you can use the following credentials:  

**User 1:**  
Username: Maite  
Password: 12  

**User 2:**  
Username: test  
Password: 123  

### ■ Development Challenges  
🔴 **Email System**: We attempted to integrate an SMTP-based password recovery system but faced difficulties with free online services. Google’s SMTP services were also not viable.  
🔴 **Design Issues**: Our initial designs were made in Adobe XD, but exporting to HTML required multiple conversions through **Figma**, leading to additional manual adjustments.  
🔴 **Flask GET/POST Handling**: We faced challenges understanding the complexity of handling user inputs and database interactions properly.  

### ■ Possible Improvements  
🔹 Implement password recovery via email  
🔹 Allow users to comment on and rate recipes  
🔹 Enforce stronger password security rules (special characters, numbers, length restrictions)  
🔹 Optimize database storage by limiting text field character count  
🔹 Enhance the **recipe display UI** for a better user experience (smartphone-style icons, subcategories, etc.)  
🔹 Improve SEO for better search visibility  

## ▌ Installation & Usage
1️⃣ **Clone the repository**
```sh
git clone https://github.com/ai-dg/cs50x.git  
cd cs50x
```

### ■ Installing final project
▸ Installing dependencies:
```sh
pip install flask
pip install flask_mail
pip install flask_session
pip install cs50
cd Week\ 10/Final\ Project/project/
flask run
```

## 📜 License
This repository contains my personal solutions and projects from CS50x.  
All code follows **CS50’s academic honesty policy** and is meant for **learning purposes only**.  
