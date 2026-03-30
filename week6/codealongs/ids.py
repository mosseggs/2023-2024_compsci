def student_id(name):
	if name == "Alice":
		return 100
	elif name == "Bob":
		return 101
	else:
		return 102

students = ['Alice', 'Bob', 'Charlie']

student_ids = {}

for student in students:
	id = student_id(student)
	student_ids[student] = id

# {'Alice': 100, 'Bob': 101, 'Charlie': 102}
print(student_ids)