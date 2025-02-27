# Library Management System

This project is a basic Library Management System built using C++. It allows an admin to add books to the library, and users can view, issue, and return books. The system stores book data in a file for persistence across sessions.

## Features
- **Admin Functionality**: 
  - Add new books to the library.
  - Store book information (ID, title, author, status) in a file.

- **User Functionality**:
  - View available books.
  - Issue books by book ID.
  - Return issued books.

## How to Use

### 1. Admin - Add Books
Admins can add new books to the library using the `addBook` function. Each book has a unique ID, title, and author. The book data is stored in a file so that it persists between program executions.

### 2. User - View Books
Users can view all books, including their ID, title, author, and whether they are issued or available.

### 3. Issue Books
Users can issue books by entering the book's unique ID. Once issued, the book's status is updated to "Issued."

### 4. Return Books
Users can return issued books by entering the book's unique ID. Once returned, the book's status is updated to "Available."

## Project Structure

