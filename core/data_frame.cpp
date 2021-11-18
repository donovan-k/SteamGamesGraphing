#include "data_frame.h"

using std::cout;
using std::endl;

DataFrame::DataFrame(std::string filename, int n_rows, bool has_col_names) {
    n_rows_ = n_rows;
    filename_ = filename;
    createStringValues(has_col_names);
}

void DataFrame::createStringValues(bool has_col_names) {
    // read in file, return when invalid
    std::ifstream in(filename_);
    if (in.fail()) return;

    // read first row as the column names
    if (in.good() && has_col_names) {
        column_names_ = csv_read_row(in, ',');

        // initialize map keys/columns to empty vectors
        for (auto col : column_names_) {
            string_values_[col] = vector<string>();
        }
    }

    int counter = 0; // counter for reading only n_rows_
    if (n_rows_ == 0) {
        n_rows_ = INT32_MAX;
    }

    // read rest of file row by row
    while (in.good() && counter < n_rows_) {
        vector<string> row = csv_read_row(in, ',');

        // put the row values in the correct column
        for (size_t i = 0; i < column_names_.size(); i++) {
            string_values_[column_names_[i]].push_back(row[i]);
        }
    }

    // increment counter
    counter++;
}

vector<string> DataFrame::csv_read_row(string &line, char delimiter) {
    std::stringstream ss(line);
    return csv_read_row(ss, delimiter);
}

vector<string> DataFrame::csv_read_row(istream &in, char delimiter) {
    std::stringstream ss;
    bool inquotes = false;
    std::vector<std::string> row;//relying on RVO
    while(in.good())
    {
        char c = in.get();
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