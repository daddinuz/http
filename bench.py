import requests

status = 0
url = 'https://api.github.com/repos/daddinuz/http/issues'
headers = {
    'Accept': 'application/vnd.github.v3+json',
    'Content-Type': 'application/json',
    'User-Agent': 'daddinuz/http'
}

response = requests.get(url, headers=headers)
status = response.status_code

exit(not (200 == status))
