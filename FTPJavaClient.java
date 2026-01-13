import org.apache.commons.net.ftp.FTPClient;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;

public class FtpExample {

    public static void main(String[] args) {
        String server = "asss.com"; //e.g., "192.168.1.100" or "ftp.example.com"
        int port = 21; // Default FTP port
        String user = "hpkas";
        String pass = "Azm@1234";

        FTPClient ftpClient = new FTPClient();

        try {
            ftpClient.connect(server, port);
            ftpClient.login(user, pass);
            ftpClient.enterLocalPassiveMode(); // Essential for many firewalls

            // --- Uploading a file ---
            String localFilePath = "local_file_to_upload.txt"; // Replace with your local file
            String remoteUploadPath = "/remote/path/on/server/uploaded_file.txt"; // Replace with remote path
            try (InputStream inputStream = new FileInputStream(localFilePath)) {
                System.out.println("Start uploading file: " + localFilePath);
                boolean uploaded = ftpClient.storeFile(remoteUploadPath, inputStream);
                if (uploaded) {
                    System.out.println("File uploaded successfully.");
                } else {
                    System.out.println("File upload failed.");
                }
            }

            // --- Downloading a file ---
            String remoteDownloadPath = "/remote/path/on/server/file_to_download.txt"; // Replace with remote file
            String localDownloadPath = "downloaded_file.txt"; // Replace with local path
            try (OutputStream outputStream = new FileOutputStream(localDownloadPath)) {
                System.out.println("Start downloading file: " + remoteDownloadPath);
                boolean downloaded = ftpClient.retrieveFile(remoteDownloadPath, outputStream);
                if (downloaded) {
                    System.out.println("File downloaded successfully.");
                } else {
                    System.out.println("File download failed.");
                }
            }

        } catch (IOException ex) {
            System.out.println("Error: " + ex.getMessage());
            ex.printStackTrace();
        } finally {
            try {
                if (ftpClient.isConnected()) {
                    ftpClient.logout();
                    ftpClient.disconnect();
                }
            } catch (IOException ex) {
                ex.printStackTrace();
            }
        }
    }
}







