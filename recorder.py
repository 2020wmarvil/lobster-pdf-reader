import PyPDF2 

infile = open('../commie.pdf', 'rb')

pdf = PyPDF2.PdfFileReader(infile)

words = []

for x in range(0, pdf.numPages):
    page = pdf.getPage(x);

    new_words = page.extractText().split()

    for word in new_words:
        if word not in words:
            words.append(word)

for word in words:
    print(word)

infile.close();
