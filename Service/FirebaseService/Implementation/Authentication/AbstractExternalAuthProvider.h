/*
* AbstractExternalAuthProvider.h
* Author: Trung La
* Date: 2024-11-24
* This is an abstract class for external authentication providers
*/

#ifndef ABSTRACTEXTERNALAUTHPROVIDER_H
#define ABSTRACTEXTERNALAUTHPROVIDER_H

class FirebaseAuthentication;

class AbstractExternalAuthProvider
{
public:
    AbstractExternalAuthProvider(const FirebaseAuthentication *firebaseAuth)
        : m_firebase(firebaseAuth)
    {
    }
    virtual ~AbstractExternalAuthProvider() = default;

    AbstractExternalAuthProvider(const AbstractExternalAuthProvider&) = delete;
    AbstractExternalAuthProvider& operator=(const AbstractExternalAuthProvider&) = delete;
    AbstractExternalAuthProvider(AbstractExternalAuthProvider&&) = delete;
    AbstractExternalAuthProvider& operator=(AbstractExternalAuthProvider&&) = delete;

    virtual bool signIn() = 0;

protected:
    const FirebaseAuthentication *m_firebase;
};

#endif // ABSTRACTEXTERNALAUTHPROVIDER_H
