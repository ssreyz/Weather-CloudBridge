import json
import boto3
import time
from decimal import Decimal

dynamodb = boto3.resource('dynamodb', region_name='us-east-1')  # Change to your region
table = dynamodb.Table('esp_lambda_table')


def convert_floats_to_decimal(obj):
    """Recursively convert all floats in a dict/list to Decimal"""
    if isinstance(obj, list):
        return [convert_floats_to_decimal(item) for item in obj]
    elif isinstance(obj, dict):
        return {key: convert_floats_to_decimal(value) for key, value in obj.items()}
    elif isinstance(obj, float):
        return Decimal(str(obj))
    else:
        return obj

def lambda_handler(event, context):

    try:
        
        dynamodb_client = boto3.client('dynamodb')
        try:
            tables = dynamodb_client.list_tables()
            print(f"Tables found in {dynamodb_client.meta.region_name}: {tables['TableNames']}")
        except Exception as list_error:
            print(f"Error listing tables: {str(list_error)}")
        
        # Try to describe the specific table
        try:
            table_description = dynamodb_client.describe_table(TableName='esp_lambda_table')
            print(f"Table esp_lambda_table found!")
            print(f"Table ARN: {table_description['Table']['TableArn']}")
        except Exception as describe_error:
            print(f"Error describing table: {str(describe_error)}")
        
        # Now try to write
        dynamodb = boto3.resource('dynamodb')
        table = dynamodb.Table('esp_lambda_table')
        
        if 'timestamp' not in event:
            event['timestamp'] = int(time.time())
        
        item = convert_floats_to_decimal(event)
        
        response = table.put_item(Item=item)
        
        print(f"Successfully wrote to DynamoDB!")
        
        return {
            'statusCode': 200,
            'body': json.dumps('Success')
        }
        
    except Exception as e:
        print(f"FULL ERROR: {str(e)}")
        import traceback
        print(f"TRACEBACK: {traceback.format_exc()}")
        raise e

