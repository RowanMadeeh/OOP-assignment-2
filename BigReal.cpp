#include "BigReal.h"

bool check_number(string realNumber)
{
    regex match("[+-]?[0-9]+(.)?[0-9]*");
    if(!regex_match(realNumber, match))
    {
        cout<<"Invalid input!"<<endl;
        return false;
    }
    else
    {
        return true;
    }
}

void remove_zeros(string& num)
{
    while(num[1]=='0' && num[2]!='.' && num.length()!=2)
    {
        num.erase(1,1);
    }

    int index=-1;

    // 3lshan maishelsh el 0 lw el rkm mn 8er point w keda mslan "300"
    bool point_check=false;

    for(int i=0; i<num.length(); i++)
    {
        if(num[i]=='.')
        {
            point_check = true;
            break;
        }
    }

    if(point_check)
    {
        for(int i=num.length()-1; i>=1; i--)
        {
            if(num[i]=='0' && num[i-1]!='.' && num.length()!=2)
            {
                index=i;
            }
            else
            {
                break;
            }
        }
        if(index!=-1)
        {
            num.erase(index,num.length()-index);
        }
    }
}

void BigReal::assign(string realNumber)
{
    if(check_number(realNumber))
    {
        if(realNumber[0]!='-' && realNumber[0]!='+')
        {
            realNumber.insert(0,1,'+');
        }

        remove_zeros(realNumber);

        num=realNumber;

        string n="";
        int index=-1;

        for(int i=0; i<num.length(); i++)
        {
            if(num[i]!='.')
            {
                n+=num[i];
            }
            else
            {
                index=i;
                break;
            }
        }
        before.setNumber(n);
        n="";
        n+=num[0];
        if(index!=-1)
        {
            for(int i=index+1; i<num.length(); i++)
            {
                n+=num[i];
            }
            after.setNumber(n);
        }
        else
        {
            after.setNumber("+0");
        }
    }
}

BigReal::BigReal(string realNumber)
{
    assign(realNumber);
}

BigReal::BigReal(double realNumber)
{
    assign(to_string(realNumber));
}

BigReal::BigReal(BigDecimalInt realNumber)
{
    before=realNumber;
    after.setNumber("+0");
}

BigReal& BigReal::operator = (BigReal &other)
{
    // To prevent self assignments
    if(this != &other)
    {
        num = other.num;
        before = other.before;
        after = other.after;
    }
    return *this;
}

BigReal BigReal::operator + (BigReal& other)
{
    BigDecimalInt sum_before,sum_after;

    BigReal result;

    int length=max(after.getNumber().length(),other.after.getNumber().length());

    sum_before = before + other.before;

    string after0s;

    if(after.getNumber().length()!=other.after.getNumber().length())
    {
        if(after.getNumber().length()<other.after.getNumber().length())
        {
            after0s+=after.sign();
            after0s+=after.getNumber();
            after0s.insert(after.getNumber().length()+1,other.after.getNumber().length()-after.getNumber().length(),'0');
            after.setNumber(after0s);
        }
        else
        {
            after0s+=other.after.sign();
            after0s+=other.after.getNumber();
            after0s.insert(other.after.getNumber().length()+1,after.getNumber().length()-other.after.getNumber().length(),'0');
            other.after.setNumber(after0s);
        }
    }

    sum_after = after + other.after;
    string spare_after = sum_after.getNumber();

    BigDecimalInt carrypos;
    carrypos.setNumber("+1");

    BigDecimalInt carryneg;
    carryneg.setNumber("-1");

    BigDecimalInt zero("0");

    if(spare_after.length()>length && sum_after.sign()=='+')
    {
        spare_after.erase(0,1);

        sum_after.setNumber(spare_after);

        sum_before = carrypos + sum_before;
    }

    else if(spare_after.length()>length && sum_after.sign()=='-')
    {
        spare_after.erase(0,1);

        sum_after.setNumber(spare_after);

        sum_before = carryneg + sum_before;
    }

    else if(sum_after.sign()!=sum_before.sign())
    {
        string s = "1";
        s.insert(1,length,'0');
        BigDecimalInt sum(s);
        if(sum_before.sign()=='+')
        {
            if(sum_before.getNumber()=="0")
            {
                sum_before.setSign(sum_after.sign());
            }
            else
            {
                sum_before = sum_before + carryneg;
                sum_after = sum_after + sum;
            }
        }
        else
        {
            sum_before = sum_before + carrypos;
            sum_after = sum_after - sum;
        }
    }

    after0s = sum_after.sign();
    after0s += sum_after.getNumber();
    after0s.insert(1,length-sum_after.getNumber().length(),'0');
    sum_after.setNumber(after0s);
    spare_after = after0s;
    spare_after.erase(0,1);

    result.num = sum_before.sign();
    result.num += sum_before.getNumber();
    result.num += '.';
    result.num += spare_after;
    return result;
}

BigReal BigReal::operator - (BigReal& other)
{
    if(other.before.sign()=='-')
    {
        other.before.setSign('+');
        other.after.setSign('+');
    }
    else
    {
        other.before.setSign('-');
        other.after.setSign('-');
    }
    return *this + other;
}

ostream &operator << (ostream& out, BigReal& n)
{
    out << n.num ;
    return out;
}

istream& operator >> (istream& in, BigReal& n)
{
    in >> n.num ;
    BigReal a(n.num);
    n=a;
    return in;
}

bool BigReal::operator == (BigReal anotherReal)
{
    if(before==anotherReal.before && after==anotherReal.after)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BigReal::operator > (BigReal anotherReal)
{
    if(before>anotherReal.before)
    {
        return true;
    }
    else if(before<anotherReal.before)
    {
        return false;
    }
    else if(after>anotherReal.after)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool BigReal::operator < (BigReal anotherReal)
{
    if(*this > anotherReal || *this == anotherReal)
    {
        return false;
    }
    else
    {
        return true;
    }
}

int BigReal::size()
{
    return (before.size() + after.size());
}

char BigReal::sign()
{
    return before.sign();
}

BigReal::BigReal(const BigReal& other)
{
    num = other.num;
    before = other.before;
    after = other.after;
}

BigReal::BigReal(BigReal&& other)
{
    num = other.num;
    BigReal a(num);
    *this = a;
}

BigReal &BigReal::operator = (BigReal &&other)
{
    num = other.num;
    BigReal a(num);
    *this = a;
}
//hi
