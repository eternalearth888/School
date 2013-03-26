===============================================
	Maria Deslis
	csci403 - spring 2013 - Bakos
	project03
===============================================

Queries:
-----------------------------------------------
1.	return all columns in the students table
2.	return the name of all the students who graduate between 2015 and 2020
3.	return the number of students whose major and department is Computer Science
4.	return the name of all the courses in the Computer Science department
5.	return the course name and professor name of all courses and sections offered in 2012

Statements: (actually tested)
-----------------------------------------------
1.	SELECT courses.title, departments.name
		FROM courses,departments
		WHERE department_id = departments.id;
2.	SELECT students.name, departments.name
		FROM students, departments
		WHERE major_id = departments.id;
3.	SELECT name, courses.title
		FROM students, enrollments, sections, courses
		WHERE section_id = sections.id
		AND course_id = courses.id
		AND student_id = students.id;
4.	SELECT students.name, sections.professor_name, courses.title, departments.name 
		FROM students, enrollments, sections, courses, departments
		WHERE course_id = courses.id
		AND student_id = students.id
		AND section_id = sections.id
		AND department_id = departments.id
		ORDER BY students.name ASC;

QUESTION:
-----------------------------------------------
	Because the database is a collection of information.
