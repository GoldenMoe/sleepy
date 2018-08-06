"""
The following code is a modified version of code from the AWS doc.
See: https://docs.aws.amazon.com/general/latest/gr/sigv4-signed-request-examples.html#sig-v4-examples-post
It is modified to manually make HTTP requests to SQS without the SDK.
It receives a message from a queue on SQS.

The reason I wrote it is so I can understand the process of manually
authenticating against AWS, so I can do it in the Arduino code.  
"""
import sys, os, base64, datetime, hashlib, hmac, urllib, requests

# ************* REQUEST VALUES *************
method = 'GET'
service = 'sqs'
region = 'ap-southeast-2'
host ='sqs.ap-southeast-2.amazonaws.com'
account_number = '141291046059'
queueName = 'sleepyQueue'
endpoint = 'https://' + host + '/' + account_number + '/' + queueName

# Key derivation functions. See:
# http://docs.aws.amazon.com/general/latest/gr/signature-v4-examples.html#signature-v4-examples-python
def sign(key, msg):
    return hmac.new(key, msg.encode('utf-8'), hashlib.sha256).digest()

def getSignatureKey(key, dateStamp, regionName, serviceName):
    kDate = sign(('AWS4' + key).encode('utf-8'), dateStamp)
    kRegion = sign(kDate, regionName)
    kService = sign(kRegion, serviceName)
    kSigning = sign(kService, 'aws4_request')
    return kSigning

access_key = os.environ.get('AWS_ACCESS_KEY_ID')
secret_key = os.environ.get('AWS_SECRET_ACCESS_KEY')
if access_key is None or secret_key is None:
    print 'No access key is available.'
    sys.exit()

# Create a date for headers and the credential string
t = datetime.datetime.utcnow()
amz_date = t.strftime('%Y%m%dT%H%M%SZ') # Format date as YYYYMMDD'T'HHMMSS'Z'
datestamp = t.strftime('%Y%m%d') # Date w/o time, used in credential scope

canonical_uri = '/' 
canonical_headers = 'host:' + host + '\n'
signed_headers = 'host'

# Match the algorithm to the hashing algorithm you use, either SHA-1 or
# SHA-256 (recommended)
algorithm = 'AWS4-HMAC-SHA256'
credential_scope = datestamp + '/' + region + '/' + service + '/' + 'aws4_request'

canonical_querystring = 'Action=ReceiveMessage'
canonical_querystring += '&Version=2012-11-05'
canonical_querystring += '&X-Amz-Algorithm=AWS4-HMAC-SHA256'
canonical_querystring += '&X-Amz-Credential=' + urllib.quote_plus(access_key + '/' + credential_scope)
canonical_querystring += '&X-Amz-Date=' + amz_date
canonical_querystring += '&X-Amz-Expires=30'
canonical_querystring += '&X-Amz-SignedHeaders=' + signed_headers

# For GET requests, the payload is an empty string ("").
payload_hash = hashlib.sha256('').hexdigest()

# Combine elements to create canonical request
canonical_request = method + '\n' + '/141291046059/sleepyQueue' + '\n' + canonical_querystring + '\n' + canonical_headers + '\n' + signed_headers + '\n' + payload_hash
print("canonical_request:\n" + canonical_request)

# ************* TASK 2: CREATE THE STRING TO SIGN*************
string_to_sign = algorithm + '\n' +  amz_date + '\n' +  credential_scope + '\n' +  hashlib.sha256(canonical_request).hexdigest()
print("string_to_sign:  " + string_to_sign)

# ************* TASK 3: CALCULATE THE SIGNATURE *************
# Create the signing key
signing_key = getSignatureKey(secret_key, datestamp, region, service)

# Sign the string_to_sign using the signing_key
signature = hmac.new(signing_key, (string_to_sign).encode("utf-8"), hashlib.sha256).hexdigest()

# ************* TASK 4: ADD SIGNING INFORMATION TO THE REQUEST *************
canonical_querystring += '&X-Amz-Signature=' + signature

# ************* SEND THE REQUEST *************
# The 'host' header is added automatically by the Python 'request' lib.
request_url = endpoint + "?" + canonical_querystring

print '\nBEGIN REQUEST++++++++++++++++++++++++++++++++++++'
print 'Request URL = ' + request_url
r = requests.get(request_url)

print '\nRESPONSE++++++++++++++++++++++++++++++++++++'
print 'Response code: %d\n' % r.status_code
print r.text