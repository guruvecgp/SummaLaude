import requests

# The API endpoint URL
url = "https://jsonplaceholder.typicode.com/posts/1"

# Make a GET request to the API
response = requests.get(url)

# Check the status code
if response.status_code == 200:
    # Parse the JSON response
    data = response.json()
    print("GET Request Successful:")
    print(data)
else:
    print(f"Error: {response.status_code}")
