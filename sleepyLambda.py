import boto3

def lambda_handler(event, context):
    
    client = boto3.client('sqs')
    response = client.send_message(
        QueueUrl='https://sqs.ap-southeast-2.amazonaws.com/141291046059/sleepyQueue',
        MessageBody='testHowdy folks',
        DelaySeconds=0,
    )
    
    return str(response['ResponseMetadata']['HTTPStatusCode'])