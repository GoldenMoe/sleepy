import boto3

def lambda_handler(event, context):
    
    client = boto3.client('sqs')
    client.send_message(
        QueueUrl='https://sqs.us-east-1.amazonaws.com/141291046059/sleepyQueue',
        MessageBody='Howdy from Lambda',
        DelaySeconds=0,
    )
    
    return {"response": {"howdy":"well dagnabbit jimmy how the hell are ya"}}