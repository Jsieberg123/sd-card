pipeline {
    agent any

    stages {
        stage('Build') {
            steps {
                sh 'make all'
            }
        }
        stage('Deploy') {
            steps {
                sh 'zip -r generic.zip bin/generic'
                sh 'zip -r motormont.zip bin/motormont'
                sh 'zip -r temperature.zip bin/temperature'
                sh 'zip -r relay.zip bin/relay'
                sh 'md5sum generic.zip > generic.hash'
                sh 'md5sum motormont.zip > motormont.hash'
                sh 'md5sum temperature.zip > temperature.hash'
                sh 'md5sum relay.zip > relay.hash'
                sh 'cp -f generic.zip /apps/generic.zip'
                sh 'cp -f generic.hash /apps/generic.hash'
                sh 'cp -f motormont.zip /apps/motormont.zip'
                sh 'cp -f motormont.hash /apps/motormont.hash'
                sh 'cp -f temperature.zip /apps/temperature.zip'
                sh 'cp -f temperature.hash /apps/temperature.hash'
                sh 'cp -f relay.zip /apps/relay.zip'
                sh 'cp -f relay.hash /apps/relay.hash'
            }
        }
    }
}