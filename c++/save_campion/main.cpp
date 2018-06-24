#include <bits/stdc++.h>

using namespace std;

void ReplaceStringInPlace(string& subject, const string& search, const string& replace) {
    size_t pos = 0;
    while ((pos = subject.find(search, pos)) != string::npos) {
         subject.replace(pos, search.length(), replace);
         pos += replace.length();
    }
}

void ParseSourceCode(string user, const char *file_name) {
    // Read file
    ifstream input_stream(file_name);
    stringstream buffer;
    buffer << input_stream.rdbuf();
    input_stream.close();
    string str = buffer.str();

    // Destroy ending
    int pos = str.find("</pre>");
    str = str.substr(0, pos - 1);

    // Find name
    pos = str.find("</a></td><td valign=\"top\"><strong>Punctaj exemplu: </strong>");
    string name;
    for (int i = pos - 1; i; -- i)
        if (str[i] != '>')
            name += str[i];
        else
            break;
    reverse(name.begin(), name.end());
    name += ".cpp";
    name = user + "/" + name;

    // Destroy beginning
    pos = str.find("<pre class=\"courier wrap sh_cpp\">") + 33;
    str = str.substr(pos, str.size() - pos);

    // Repair '<' and '>'
    ReplaceStringInPlace(str, "&lt;", "<");
    ReplaceStringInPlace(str, "&gt;", ">");

    ofstream output_stream(name);
    output_stream << str;
    output_stream.close();
}

// <a href="index.php?page=source&amp;action=view&amp;id=
vector <int> ParseStatistics(const char *file_name) {
    // Read file
    ifstream input_stream(file_name);
    stringstream buffer;
    buffer << input_stream.rdbuf();
    input_stream.close();
    string str = buffer.str();

    // Search for fully solved problems and push them to the solution
    vector <int> ids;

    const string PATTERN = "<td align=\"center\"><a href=\"index.php?page=source&amp;action=view&amp;id=";
    int pos = str.find(PATTERN, 0);
    while (pos != string :: npos) {
        int id = 0, i;
        for (i = pos + PATTERN.size(); i < str.size(); ++ i)
            if (str[i] == '\"')
                break;
            else {
                id *= 10;
                id += str[i] - '0';
            }

        i += 2;
        if (str[i] == '1' && str[i + 1] == '0' && str[i + 2] == '0')
            ids.push_back(id);
        pos = str.find(PATTERN, pos + 1);
    }

    // Make sure there are no duplicates
    sort(ids.begin(), ids.end());
    ids.resize(unique(ids.begin(), ids.end()) - ids.begin());
    return ids;
}

void Login(string user, string password) {
    string loginCommand = "wget \"http://campion.edu.ro/arhiva/index.php?page=connect&action=connected\" --post-data \"login_name=" +
                     user +
                     "&password=" +
                     password +
                     "\" --no-check-certificate --keep-session-cookies --save-cookies=" + user + "/" + "cookies --load-cookies=" + user + "/cookies -U \"Firefox\" -S -O /dev/null";

    system(loginCommand.c_str());
}

#define SSTR( x ) static_cast< std::ostringstream & >( \
        ( std::ostringstream() << std::dec << x ) ).str()

void DownloadId(string user, int id) {
    string downloadCommand = "wget \"http://campion.edu.ro/arhiva/index.php?page=code&id=" +
                             SSTR(id) +
                             "\" --no-check-certificate --keep-session-cookies --load-cookies=" + user + "/cookies -U \"Firefox\" -S -O " +
                             user +
                             "/input_" +
                             SSTR(id);

    system(downloadCommand.c_str());
}

void DownloadStatistics(string user, int id) {
    string downloadCommand = "wget \"http://campion.edu.ro/arhiva/index.php?page=auth&id=" +
                             SSTR(id) +
                             "\" --no-check-certificate --keep-session-cookies --load-cookies=" + user + "/cookies -U \"Firefox\" -S -O " +
                             user +
                             "/" +
                             user +
                             "_profile";

    system(downloadCommand.c_str());
}

void ParseId(string user, int id) {
    ParseSourceCode(user, (user + "/input_" + SSTR(id)).c_str());
    system(("rm " + user + "/input_" + SSTR(id)).c_str());
}

void ProcessId(string user, int id) {
    DownloadId(user, id);
    ParseId(user, id);
}

void DownloadUserCodes(string user, string password, int id) {
    system(("rm -r " + user).c_str());
    system(("mkdir " + user).c_str());

    Login(user, password);
    DownloadStatistics(user, id);

    vector <int> ids = ParseStatistics((user + "/" + user + "_profile").c_str());

    int cnt = 0;
    for (auto it: ids) {
        ProcessId(user, it);
        cout << "Done with " << (++ cnt) << endl;
    }

    cout << "Successfully saved " << ids.size() << " jobs!" << endl;

    system(("rm " + user + "/cookies").c_str());
    system(("rm " + user + "/" + user + "_profile").c_str());
    system("rm wget-log");
}

int main() {
    string user, password;
    int id;

    cout << "CAUTION! Only to be run on LINUX machines." << endl;
    cout << endl;
    cout << "User: "; cin >> user;
    cout << "Password: "; cin >> password;
    cout << "ID (found in the URL of the profile page): "; cin >> id;

    DownloadUserCodes(user, password, id);
    return 0;
}
