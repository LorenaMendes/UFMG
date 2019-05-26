#ifndef CLASSES_H
#define CLASSES_H

class ClasseBase
{
public:
    int var_public;
private:
    int var_private;
protected:
    int var_protected;

public:
    void set_public(int);
    int get_public();
    void set_private(int);
    int get_private();
    void set_protected(int);
    int get_protected();
};


class A2 : private ClasseBase 
{
public:
	int var_public2;
private:
	int var_private2;
protected:
	int var_protected2;

public:
    void set_public2(int); 
    int get_public2();
    void set_private2(int); 
    int get_private2();
    void set_protected2(int);
    int get_protected2();

    void set_public_base_a2(int);
    int get_public_base_a2();
    void set_protected_base_a2(int);
    int get_protected_base_a2();
};


class A3 : public A2
{
public:
	int var_public3;
private:
	int var_private3;
protected:
	int var_protected3;

public:
    void set_public3(int var);
    int get_public3();
    void set_protected3(int var);
    int get_protected3();
    void set_private3(int var);
    int get_private3();

    void set_public_a3_a2(int var);
    int get_public_a3_a2();
    void set_protected_a3_a2(int var);
    int get_protected_a3_a2();
}; 


class ClassePublica : public ClasseBase
{
public:
	int var_public3;
private:
	int var_private3;
protected:
	int var_protected3;
	
public:
    ClassePublica()
    {
        var_public = 0;
        var_protected = 0; 
    }

    void set_public_public_base(int val);
    int get_public_public_base();
    void set_protected_public_base(int val);
    int get_protected_public_base();
}; 


class ClassePrivada : private ClasseBase
{
public:
    ClassePrivada()
    {
        var_public = 0; 
        var_protected = 0; 
    }

    void set_public_private_base(int val);
    int get_public_private_base();
    void set_protected_private_base(int val);
    int get_protected_private_base();
};

class OverloadPrivada : private ClasseBase
{
	public:
    	int var_public;
	private:
    	int var_private;
	protected:
    	int var_protected;

    public:
        void set_public(int val);
        int get_public();
        void set_protected(int val);
        int get_protected();
        void set_private(int val);
        int get_private();
};

#endif