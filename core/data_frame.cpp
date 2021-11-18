#include "data_frame.h"

using std::cout;
using std::endl;

DataFrame::DataFrame(std::string filename, int n_rows) {
    n_rows_ = n_rows;
    filename_ = filename;
    createStringValues();
}

void DataFrame::createStringValues() {
    // read in file, return when invalid
    std::ifstream in(filename_);
    if (in.fail()) return;

    // rows to read (if default(0) then read all)
    if (n_rows_ == 0) {
        n_rows_ = INT32_MAX;
    }

    // read file row by row
    int counter = 0;
    while(in.good() && counter < n_rows_)
    {
        std::vector<std::string> row = csv_read_row(in, ',');
        cout << "good" << endl;

        // initialize column values when reading the first row
        if (counter == 0) {
            column_names_ = row;
            for (auto col : column_names_) {
                string_values_[col] = vector<string>();
            }
            counter++;
            continue;   
        }

        // set the correct row and column index to the correct key in string values
        for (size_t i = 0; i < row.size(); i++) {
            string_values_[column_names_[i]].push_back(row[i]);
        }

        // increment counter
        counter++;
    }

    // close file
    in.close();
}

std::vector<std::string> DataFrame::csv_read_row(std::istream &in, char delimiter)
{
    std::stringstream ss;
    bool inquotes = false;
    std::vector<std::string> row;//relying on RVO
    while(in.good())
    {
        char c = in.get();
        cout << c << " " << std::flush;
        if (!inquotes && c=='"') //beginquotechar
        {
            inquotes=true;
        }
        else if (inquotes && c=='"') //quotechar
        {
            if ( in.peek() == '"')//2 consecutive quotes resolve to 1
            {
                ss << (char)in.get();
            }
            else //endquotechar
            {
                inquotes=false;
            }
        }
        else if (!inquotes && c==delimiter) //end of field
        {
            row.push_back( ss.str() );
            ss.str("");
        }
        else if (!inquotes && (c=='\r' || c=='\n') )
        {
            if(in.peek()=='\n') { in.get(); }
            row.push_back( ss.str() );
            return row;
        }
        else
        {
            ss << c;
        }
    }
}