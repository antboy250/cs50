import urllib.request, json
import cs50

# sym=cs50.get_string("symbol")

with urllib.request.urlopen('https://www.alphavantage.co/query?function=TIME_SERIES_INTRADAY&symbol=MSFT&interval=1min&apikey=demo') as url:
    data = json.loads(url.read().decode())
    print(data)