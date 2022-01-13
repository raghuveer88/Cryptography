#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include<conio.h>
#include<time.h>

char array[26] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
char cap_array[26] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
int MAX = 5;
int selected;

char *read_file()
{
    char ch;
    char file_name[] = "process.txt";
    char *input;
    FILE *fp;
    fp = fopen(file_name, "r");
    if (fp == NULL)
    {
        perror("Error while opening the file.\n");
        exit(EXIT_FAILURE);
    }

    if (fgets(input, 60, fp) != NULL)
    {
        /* writing content to stdout */
    }

    fclose(fp);
    return input;
}

char *removeSpaces(char *arr)
{
    int x = 0, z = 0; //variables to track and remove the white spaces
    while (arr[x])
    {
        if (arr[x] != ' ')
            arr[z++] = arr[x];
        x++;
    }
    arr[z] = '\0';
    return arr;
}

char *removeDuplicates(char *str)
{
    int i, j, k;
    for (i = 0; i < strlen(str); i++)
    {
        for (j = i + 1; str[j] != '\0'; j++)
        {
            if (str[j] == str[i])
            {
                for (k = j; str[k] != '\0'; k++)
                {
                    str[k] = str[k + 1];
                }
            }
        }
    }
    return str;
}

int binarySearch(char arr[], int low, int high, char search_element)
{
    if (high >= low)
    {
        int mid = low + (high - low) / 2;
        if (arr[mid] == search_element)
            return mid;

        if (arr[mid] > search_element)
            return binarySearch(arr, low, mid - 1, search_element);

        return binarySearch(arr, mid + 1, high, search_element);
    }
    return -1;
}

// -----------------------caesar code -------------------------------------------

int caesar_encript(char *plaintext, int key)
{
    char ciphertext[strlen(plaintext)];
    for (int i = 0; i < strlen(plaintext); i++)
    {
        int index = binarySearch(array, 0, 25, plaintext[i]);
        // printf("%d\n",a);
        int cipher = (index + key) % 26;
        if (cipher < 0)
        {
            cipher = 26 - cipher;
        }
        ciphertext[i] = array[cipher];
    }
    ciphertext[strlen(plaintext)] = '\0';
    printf("%s\n", ciphertext);
}

int caesar_decript(char *ciphertext, int key)
{
    char plaintext[strlen(ciphertext)];
    for (int i = 0; i < strlen(ciphertext); i++)
    {
        int index = binarySearch(array, 0, 25, ciphertext[i]);
        // printf("%d\n",a);
        int cipher = (index - key) % 26;
        if (cipher < 0)
        {
            cipher = 26 + cipher;
        }
        plaintext[i] = array[cipher];
    }
    plaintext[strlen(ciphertext)] = '\0';
    printf("%s\n", plaintext);
}

// ----------------------vigenere code -----------------------------------

int vigenere_encript(char *plaintext, char *key)
{
    char ciphertext[strlen(plaintext)];
    int key_indexs[strlen(key)];
    int key_index_track = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        int key_index = binarySearch(array, 0, 25, key[i]);
        key_indexs[i] = key_index;
        // printf("%d\n",key_indexs[i]);
    }
    key_indexs[strlen(key)] = '\0';
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (plaintext[i] == ' ')
        {
            ciphertext[i] = ' ';
        }
        else
        {
            int index = binarySearch(array, 0, 25, plaintext[i]);
            int cipher = (index + key_indexs[key_index_track % strlen(key)] + 1) % 26;
            ciphertext[i] = array[cipher];
            key_index_track++;
        }
    }
    ciphertext[strlen(plaintext)] = '\0';
    printf("%s\n", ciphertext);
}

int vigenere_decript(char *ciphertext, char *key)
{
    char plaintext[strlen(ciphertext)];
    int key_indexs[strlen(key)];
    int key_index_track = 0;
    for (int i = 0; i < strlen(key); i++)
    {
        int key_index = binarySearch(array, 0, 25, key[i]);
        key_indexs[i] = key_index;
        //printf("%d\n",key_indexs[i]);
    }
    key_indexs[strlen(key)] = '\0';
    for (int i = 0; i < strlen(ciphertext); i++)
    {
        if (ciphertext[i] == ' ')
        {
            plaintext[i] = ' ';
        }
        else
        {
            int index = binarySearch(array, 0, 25, ciphertext[i]);
            int cipher = (index - key_indexs[key_index_track % strlen(key)] - 1) % 26;
            if (cipher < 0)
            {
                cipher = 26 + cipher;
            }
            plaintext[i] = array[cipher];
            key_index_track++;
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
    printf("%s\n", plaintext);
}

// ----------------------playfair code-----------------------------

void eliminateDups(char word[])
{

    int i = 0;
    int map[256] = {0};
    int last_index = 0;
    while (*(word + i))
    {
        char temp = *(word + i);
        if (0 == map[temp])
        {
            map[temp] = 1;
            *(word + last_index) = temp;
            last_index++;
        }
        i++;
    }
    *(word + last_index) = '\0';
}

void play_Fair(char key[MAX][MAX], char letter1, char letter2)
{
    int a;
    int b;
    int k;
    int d;
    int e;
    int c;
    for (a = 0; a < MAX; a++)
    {
        for (b = 0; b < MAX; b++)
        {
            if (letter1 == key[a][b])
            {
                k = a;
                c = b;
            }
            else if (letter2 == key[a][b])
            {
                d = a;
                e = b;
            }
        }
    }
    if (k == d)
    {
        if (selected == 1)
        {
            c = (c + 1) % 5;
            e = (e + 1) % 5;
        }
        else
        {
            c = ((c - 1) % 5 + 5) % 5;
            e = ((e - 1) % 5 + 5) % 5;
        }
        printf("%c%c", key[k][c], key[d][e]);
    }
    else if (c == e)
    {
        if (selected == 1)
        {
            k = (k + 1) % 5;
            d = (d + 1) % 5;
        }
        else
        {
            k = ((k - 1) % 5 + 5) % 5;
            d = ((d - 1) % 5 + 5) % 5;
        }
        printf("%c%c", key[k][c], key[d][e]);
    }
    else
    {
        printf("%c%c", key[k][e], key[d][c]);
    }
}

void playfair(char* str)
{
    int i, j, k = 0, l, m = 0, n;
    char key[MAX][MAX], keyminus[25], keystr[10];

    printf("1-Encryption\n2-Decryption\n");
    printf("choose anyone: ");
    scanf("%d", &selected);
    if (selected != 1 && selected != 2)
    {
        printf("Invalid Choice");
        return;
    }
    fflush(stdin);
    printf("\nEnter key:");
    gets(keystr);
    // printf("\nEnter the text:");
    // gets(str);
    eliminateDups(keystr);
    n = strlen(keystr);
    
    for (i = 0; i < n; i++)
    {
        if (keystr[i] == 'j')
            keystr[i] = 'i';
        else if (keystr[i] == 'J')
            keystr[i] = 'I';
        keystr[i] = toupper(keystr[i]);
    }
    
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'j')
            str[i] = 'i';
        else if (str[i] == 'J')
            str[i] = 'I';
        str[i] = toupper(str[i]);
    }
    
    j = 0;
    for (i = 0; i < 26; i++)
    {
        for (k = 0; k < n; k++)
        {
            if (keystr[k] == cap_array[i])
                break;
            else if (cap_array[i] == 'J')
                break;
        }
        if (k == n)
        {
            keyminus[j] = cap_array[i];
            j++;
        }
    }
    
    k = 0;
    for (i = 0; i < MAX; i++)
    {
        for (j = 0; j < MAX; j++)
        {
            if (k < n)
            {
                key[i][j] = keystr[k];
                k++;
            }
            else
            {
                key[i][j] = keyminus[m];
                m++;
            }
            printf("%c ", key[i][j]);
        }
        printf("\n");
    }
    
    printf("\nEntered text :%s\nOutput Text :", str);
    for (i = 0; i < strlen(str); i++)
    {
        if (str[i] == 'J')
            str[i] = 'I';
        if (str[i + 1] == '\0')
            play_Fair(key, str[i], 'X');
        else
        {
            if (str[i + 1] == 'J')
                str[i + 1] = 'I';
            if (str[i] == str[i + 1])
                play_Fair(key, str[i], 'X');
            else
            {
                play_Fair(key, str[i], str[i + 1]);
                i++;
            }
        }
    }
    if (selected == 2)
        printf(" (Do not consider unnecessary X)");
}

//-------------------------------Caesar Cipher Cryptanalysis----------------------

void caesar_cipher(){
    int count[26] = {0};
    char cipher_text[] = "TYHHEHZHTCPWPDDCLOTZNZXXFYTNLETZYHLDGPCJTXAZCELYEQZCOTCPNETYRXTWTELCJQZCNPDDACPLOLWWZGPCESPHZCWOMFECLOTZXPDDLRPDNZFWOMPTYEPCNPAEPODZDPNCPETYQZCXLETZYAWLYDLYOZCOPCDSLOEZMPECLYDXTEEPOTYDPNCPENZOPDLWWESPXLUZCAZHPCDFDPONZXAWPIXLNSTYPDESLEEFCYPOZCOTYLCJEPIETYEZDPNCPENZOPLRPCXLYXLNSTYPNLWWPOPYTRXLLYOLYLXPCTNLYOPGTNPVYZHYLDDTRLMLLCPZYOTDAWLJTYLYPISTMTETYESPYLETZYLWXFDPFXZQEPSFYTEPODELEPDLTCQZCNPESPLWWTPDHPCPLMWPEZCPLORPCXLYXPDDLRPDGPCJPLCWJTYESPHLCESLYVDEZMCTWWTLYEHZCVMJAZWTDSLYOMCTETDSXLESPXLETNTLYDTYESPESTCETPDAZWTDSNCJAELYLWJDEDLVLNZOPMCPLVTYRPIAPCEDNZATPOESPRPCXLYPYTRXLXLNSTYPHTESESPSPWAZQLRPCXLYECLTEZCLYODZWGPOTEDWPEEPCDNCLXMWTYRALEEPCYDESPJWLEPCDSLCPOESTDVYZHWPORPHTESQCLYNPLYOMCTELTYTYEPWWTRPYNPQCZXOPNCJAEPOPYTRXLXPDDLRPDNZOPYLXPOFWECLHLDPIECPXPWJDPNCPELYOGPCJQPHAPZAWPVYPHLMZFETEHSTWPESPRPCXLYDYPGPCQZFYOZFEESPLWWTPDNZFWODZWGPESPTCNZOPDESPJDFDAPNEPOTELDESPTCLMTWTEJEZDTYVLWWTPODSTAATYRDWTAAPOOCLXLETNLWWJTYQZCEJEHZESTDWPOESPRPCXLYYLGJEZLOOLYLOOTETZYLWCZEZCEZESPTCPYTRXLXLNSTYPDLYOESPDFMXLCTYPHZWQALNVDZYNPLRLTYDELCEPOELVTYRESPTCEZWWZQDSTAATYR";
    for (int i = 0; i < strlen(cipher_text); i++)
    {
        if (cipher_text[i] == 'A')
        {
            count[0] += 1;
        }
        if (cipher_text[i] == 'B')
        {
            count[1] += 1;
        }
        if (cipher_text[i] == 'C')
        {
            count[2] += 1;
        }
        if (cipher_text[i] == 'D')
        {
            count[3] += 1;
        }
        if (cipher_text[i] == 'E')
        {
            count[4] += 1;
        }
        if (cipher_text[i] == 'F')
        {
            count[5] += 1;
        }
        if (cipher_text[i] == 'G')
        {
            count[6] += 1;
        }
        if (cipher_text[i] == 'H')
        {
            count[7] += 1;
        }
        if (cipher_text[i] == 'I')
        {
            count[8] += 1;
        }
        if (cipher_text[i] == 'J')
        {
            count[9] += 1;
        }
        if (cipher_text[i] == 'K')
        {
            count[10] += 1;
        }
        if (cipher_text[i] == 'L')
        {
            count[11] += 1;
        }
        if (cipher_text[i] == 'M')
        {
            count[12] += 1;
        }
        if (cipher_text[i] == 'N')
        {
            count[13] += 1;
        }
        if (cipher_text[i] == 'O')
        {
            count[14] += 1;
        }
        if (cipher_text[i] == 'P')
        {
            count[15] += 1;
        }
        if (cipher_text[i] == 'Q')
        {
            count[16] += 1;
        }
        if (cipher_text[i] == 'R')
        {
            count[17] += 1;
        }
        if (cipher_text[i] == 'S')
        {
            count[18] += 1;
        }
        if (cipher_text[i] == 'T')
        {
            count[19] += 1;
        }
        if (cipher_text[i] == 'U')
        {
            count[20] += 1;
        }
        if (cipher_text[i] == 'V')
        {
            count[21] += 1;
        }
        if (cipher_text[i] == 'W')
        {
            count[22] += 1;
        }
        if (cipher_text[i] == 'X')
        {
            count[23] += 1;
        }
        if (cipher_text[i] == 'Y')
        {
            count[24] += 1;
        }
        if (cipher_text[i] == 'Z')
        {
            count[25] += 1;
        }
    }

    // for (int i = 0; i < 26; i++)
    // {
    //     printf("%d) %d\n", i, count[i]);
    // }

    int max = count[0];
    int index_max;
    for (int i = 0; i < 26; i++)
    {
        if (max < count[i])
        {
            max = count[i];
            index_max = i;
        }
    }
    // printf("%d %d", index_max, max);
    int key = (index_max - 4) % 26;
    printf("The key for this text is %d\n", key);
    printf("The orginal plaintext is \n");
    for(int i = 0;i<strlen(cipher_text);i++){
        int cipher_index = binarySearch(cap_array,0,25,cipher_text[i]);
        int plain_index = cipher_index-key;
        if (plain_index < 0)
            {
                plain_index += 26;
            }
            printf("%c", cap_array[plain_index]);
        
    }
}

// -----------------------Vigenere Cipher Cryptanalysis -----------------------------------------
void vigenere_cipher(){
    char key[] = "TURING";
    char cipher_text[] = "HHKMAZAMVXGKFVVZROZBKGFOQWCQSLLNFTYGLSJBRSLUUUVTBMKZNZHLRBGNXFREEKGWVJRXDYCMLTTNZWAGEFRJBXTNFZLOGWRTVLHLEQNITFCMQIAOTSZIGUKBNZMBVKBSIOKMEIXHKZRUYNYMNTGCJBBTTLDGQKIIKQAGEUSIZGMIZVSUKGYQZZAUKIUGVEVZPGEFVLGNXBLVGKKQRAOXXUBQAMBHKWUOLWFUCAMYIALYMYDAGNXBRKXKKQRVGKWNFMKZKUTBVTYIIUNZBIENEUFNYMHYTLDGEKWMKWAKKITSRZMYJBFOMYFVHYFCJAVRXNVAGYKYCIGKWNFXEKLCUMAZKIEIYJKYRONTLZCITYACGAGXTNVOVIWYWMAIXCEQGOTNZDRTBWBVNSXXJBNXPUIAGNBMNIFUGYFNGNXZZZFZDHFEAIRVVZRYICFVNMXIGMEGMCFVFKGAZVRKKYUJLSHMTWJOGWFWCKKUKQBTPCKPRGLNXMESTHPITGBHJBGNXOJUVRBNRZLZAYYCAZYIIPHTMYIAGGKNVLNYTKLMFZMIWQAJHOKEUUHLNPNZTWTWHTMCEORXKIIORTXLRBRJTMVDRTMSWQIKVYEBFNHLKNNREZFZAOGYJMPUGXJWSVAIEMHYXCEBUKEUSWEGMIIGEKVYZXGYYIIKBSIOKMEALYSGBZAYILRVTLKURTMMCIKYXWLZVZRJIIPZBWVANZMBVBVSXYMMAOGNYMZOECKIEEXMKIORBMYURTMGVIAZMBRBPUFJLBRXLSJBRSLUELAKMQFZXYPYIMRGLSKIEMXNJNBXAUTSRXLOJMEYHZTWZVNNVZFOGNYMVTGYIANTVNLUBLMBVCFSBFZBNXRIWBRTLCDXYENMVLGNXQFZQVTMJEBXWUJBUKBLGIFYPIILGNXWZISHBUELAYTBRLAUMLVIYRRXVIYZPCKPUGVEZVTHXZFZROGNVTYOZYEKRUYZZKVGEMNMEKDYVVGUUYZVSUKGVLOELNFTYHNNZBJGLOEKYKTLLVQKKQYIGJXJRZGSXHKAWAKCJLVIMCFVFAVBYIPQBHXIPZBPZBVKLZVTYALCEBRRECXMAIXZZVNRESXWGZAYZZNIMNFORZAYIIAJMBIMREXUIAYGMYIQAKBAYBLTBHVBEGVEVLGNXBRKXKKMUWJTTHUQAIHIGMEGMCFVJOMBKPRCXMKORXFUEIHZAIIQGOXMRZEKLNVLSOOYTCYVKCKAVTTHUIEUNHUPNTHPVZNSHHXBUKFQRAUGGIMMEAGCMMEYBNPXUELCTAFZNXVVGSTLBCFNXMJEUUAUUBRGFYUCCCBNYARBXLRTBZAYIPNIDYIAGUVICTRIMMVVFOMCMMVTYIIUNZBIEEUOVBNIFRTNVZFUEXKWGNXEXJVTXRTPNTZYWWELBZKGSUNLKPBALUELQUEFRZFGGXHCNTMCKQRYHZTWPGBHVBUKAUTSRXLGRVNMXXKWNZMUTSSUNLYCAJKYUNVLMSLAZOECKIEEVIDXHZXLJIAJLOGXYOXXKPRQZVNQGNMBFCFGGXJWSVTAVABLILZVGUNNJWSALWCIFYBZZMQJHWLURTMMGIFYPIILFLHLLAZOECKIEEVIDXHZXLJIAJWYKIVRLIWBUKAUTSRXLINVZKMBFLFGGXKMPNGCHCRYAINBBHKYRSVTMIJXRIBZZKIGQWFUCAMYIAJNBWYVRZPIISFZHOJMNYPYCTNYBHWWESTNZWAUGBFEZOECKIEEGYKEBXDMFXRXTNVL";
    int cipher_text_len = strlen(cipher_text);
    int index_temp;
    int index_temp1;
    int index_temp2;
    
    printf("key is %s\n",key);
    // printf("%d", cipher_text_len);
    for (int i = 0; i < strlen(cipher_text); i++)
    {
        int index = i % 6;
        if (index == 0)
        {
            index_temp = binarySearch(cap_array, 0, 25, cipher_text[i]);
            index_temp1 = binarySearch(cap_array, 0, 25, key[index]);
            index_temp2 = index_temp - index_temp1;
            if (index_temp2 < 0)
            {
                index_temp2 += 26;
            }
            printf("%c", cap_array[index_temp2]);
        }
        if (index == 1)
        {
            index_temp = binarySearch(cap_array, 0, 25, cipher_text[i]);
            index_temp1 = binarySearch(cap_array, 0, 25, key[index]);
            index_temp2 = index_temp - index_temp1;
            if (index_temp2 < 0)
            {
                index_temp2 += 26;
            }
            printf("%c", cap_array[index_temp2]);
        }
        if (index == 2)
        {
            index_temp = binarySearch(cap_array, 0, 25, cipher_text[i]);
            index_temp1 = binarySearch(cap_array, 0, 25, key[index]);
            index_temp2 = index_temp - index_temp1;
            if (index_temp2 < 0)
            {
                index_temp2 += 26;
            }
            printf("%c", cap_array[index_temp2]);
        }
        if (index == 3)
        {
            index_temp = binarySearch(cap_array, 0, 25, cipher_text[i]);
            index_temp1 = binarySearch(cap_array, 0, 25, key[index]);
            index_temp2 = index_temp - index_temp1;
            if (index_temp2 < 0)
            {
                index_temp2 += 26;
            }
            printf("%c", cap_array[index_temp2]);
        }
        if (index == 4)
        {
            index_temp = binarySearch(cap_array, 0, 25, cipher_text[i]);
            index_temp1 = binarySearch(cap_array, 0, 25, key[index]);
            index_temp2 = index_temp - index_temp1;
            if (index_temp2 < 0)
            {
                index_temp2 += 26;
            }
            printf("%c", cap_array[index_temp2]);
        }
        if (index == 5)
        {
            index_temp = binarySearch(cap_array, 0, 25, cipher_text[i]);
            index_temp1 = binarySearch(cap_array, 0, 25, key[index]);
            index_temp2 = index_temp - index_temp1;
            if (index_temp2 < 0)
            {
                index_temp2 += 26;
            }
            printf("%c", cap_array[index_temp2]);
        }
    }
}


int main()
{
    printf("The different encryption,decryption and cryptanalysis techniques we have are\n\n");
    printf("********NOTE - NO SPACES AND NEW LINES IN process.txt FILE**************\n\n");
    printf("1) Ceasar\n2) Vigenere\n3) PlayFair\n4) Caesar Cipher Cryptanalysis\n5) Vigenere Cipher Cryptanalysis\n");
    printf("choose anyone: ");
    int select;
    scanf("%d", &select);
    char input[3000];
    FILE *fptr;
    clock_t t;
    double time_taken;
    if ((fptr = fopen("process.txt", "r")) == NULL)
    {
        printf("Error! opening file\n");
        exit(1);
    }

    fgets(input, 2000, fptr);
    for(int i = 0;i<strlen(input);i++){
        input[i] = tolower(input[i]);
    }
    fclose(fptr);

    switch (select)
    {
    case 1:
        printf("1-Encryption\n2-Decryption\n");
        printf("choose anyone: ");
        
        int ch;
        scanf("%d", &ch);
        printf("NOTE - Give a number as key for caesar\n");
        printf("ENTER key - ");
        int key;
        scanf("%d", &key);

        if (ch == 1)
        {
            caesar_encript(input, key);
        }
        if (ch == 2)
        {
            caesar_decript(input, key);
        }
        break;

    case 2:
        printf("1-Encryption\n2-Decryption\n");
        printf("choose anyone: ");
        int ch1;
        scanf("%d", &ch1);
        printf("ENTER key - ");
        char key1[100];
        scanf("%s", &key1);
        for(int i = 0;i<strlen(key1);i++){
            key1[i] = tolower(key1[i]);
        }
        if (ch1 == 1)
        {
            vigenere_encript(input, key1);
        }
        if (ch1 == 2)
        {
            vigenere_decript(input, key1);
        }
        break;
    case 3:
        playfair(input);
        break;
    case 4:
        t = clock();
        caesar_cipher();
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        printf("\n\ncaesar cipher took %f seconds to execute \n\n", time_taken);
        break;
    case 5:
        t = clock();
        vigenere_cipher();
        t = clock() - t;
        time_taken = ((double)t)/CLOCKS_PER_SEC; // in seconds
        printf("\n\nvigenere cipher took %f seconds to execute \n\n", time_taken);
        break;
    default:
        printf("please enter a valid input\n");
        break;
    }
    //char* input = read_file();
    //caesar_encript("hello",3);
    //caesar_decript(input,3);
    //vigenere_encript("there are two ways","system");
    //vigenere_decript("lfwki mjc lps iswk","system");
    // char key[] = "raghuveer";
    // removeDuplicates(key);
    //playfair();

    return 0;
}
