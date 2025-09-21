from google import genai
import sys
from google.genai import types
import io
import pathlib
import httpx

# python3 apiHandler.py apiFilePath file1 file2 file3

apiKey=""

def setApi(apiFilePath:str):
    global apiKey

    apiFile = open(apiFilePath)

    apiKey=apiFile.read()

    apiFile.close()

def getResponse(prompt:str):
    fileList=list()
    fileList=sys.argv[2:]

    setApi(sys.argv[1])

    client = genai.Client(api_key=apiKey)

    uploadList=list()

    file=""
    for file in fileList:
        doc = -1
        if ".net/" in file or ".com/" in file or ".edu/" in file or ".org/" in file or "http://" in file or "https://" in file or ".in" in file:
            doc_io = io.BytesIO(httpx.get(file).content)
            doc = client.files.upload(
                file=doc_io,
                config=dict(mime_type='application/pdf')
            )
        if "/" not in file:
            doc_path = pathlib.Path(file)
            doc = client.files.upload(
                file=doc_path,
            )
        if file[0]=="/" and (file[::-1][0:5]=="/fpd." or file[::-1][0:5]=="fpd."):
            doc = client.files.upload(
                file=file,
            )
        
        if doc == -1:
            print(f"! couldn't parse file:: {file}")
        else:
            uploadList.append(doc)



    finalContent = uploadList
    finalContent.append(prompt)

    # print(f"\n\n@debug:: {finalContent}\n\n")

    print("\n---------------START---------------")
    response=client.models.generate_content(
        model='gemini-2.5-flash',
        contents=finalContent
    )

    print(response.text)
    print("\n----------------END----------------")
if __name__=='__main__':
    promptFile = open("promptFile.txt")
    prompt=promptFile.read()
    promptFile.close()
    getResponse(prompt)
# doc1 = "https://arxiv.org/pdf/2312.11805"
# doc2 = "file1.pdf"

