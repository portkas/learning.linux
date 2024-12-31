#include <iostream>
#include <filesystem>
#include <fstream>
#include <libssh/libssh.h>
#include <libssh/sftp.h>
#include <fcntl.h> 

namespace fs = std::filesystem;

void upload_files(const std::string& host, const std::string& user, const std::string& password, const std::string& remote_dir, const std::string& local_dir) {
    ssh_session session = ssh_new();
    if (session == nullptr) {
        std::cerr << "Error creating SSH session\n";
        return;
    }

    ssh_options_set(session, SSH_OPTIONS_HOST, host.c_str());
    ssh_options_set(session, SSH_OPTIONS_USER, user.c_str());

    if (ssh_connect(session) != SSH_OK) {
        std::cerr << "Error connecting to host: " << ssh_get_error(session) << "\n";
        ssh_free(session);
        return;
    }

    if (ssh_userauth_password(session, nullptr, password.c_str()) != SSH_AUTH_SUCCESS) {
        std::cerr << "Authentication error: " << ssh_get_error(session) << "\n";
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    sftp_session sftp = sftp_new(session);
    if (sftp == nullptr) {
        std::cerr << "Error creating SFTP session: " << ssh_get_error(session) << "\n";
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    if (sftp_init(sftp) != SSH_OK) {
        std::cerr << "Error initializing SFTP session: " << sftp_get_error(sftp) << "\n";
        sftp_free(sftp);
        ssh_disconnect(session);
        ssh_free(session);
        return;
    }

    for (const auto& entry : fs::directory_iterator(local_dir)) {
        if (entry.is_regular_file()) {
            std::string local_path = entry.path().string();
            std::string filename = entry.path().filename().string();
            std::string remote_path = remote_dir + "/" + filename;

            std::ifstream file(local_path, std::ios::binary);
            if (!file) {
                std::cerr << "Cannot open file: " << local_path << "\n";
                continue;
            }

            sftp_file remote_file = sftp_open(sftp, remote_path.c_str(), O_WRONLY | O_CREAT | O_TRUNC, S_IRWXU);
            if (remote_file == nullptr) {
                std::cerr << "Error opening remote file: " << sftp_get_error(sftp) << "\n"
                          << "File: " << remote_path << "\n";
                continue;
            }

            const int buffer_size = 4096;
            char buffer[buffer_size];
            while (file) {
                file.read(buffer, buffer_size);
                if (file.gcount() > 0) {
                    if (sftp_write(remote_file, buffer, file.gcount()) != file.gcount()) {
                        std::cerr << "Error writing to remote file: " << sftp_get_error(sftp) << "\n"
                                  << "File: " << remote_path << "\n";
                        break;
                    }
                }
            }

            sftp_close(remote_file);
            std::cout << "Uploaded: " << remote_path << "\n";
        }
    }

    sftp_free(sftp);
    ssh_disconnect(session);
    ssh_free(session);
}

int main() {
    std::string local_dir = "/path/to/local/folder"; // 监控的本地文件夹路径
    std::string remote_host = "windows_client_ip";
    std::string username = "windows_username";
    std::string password = "windows_password";
    std::string remote_dir = "C:/path/to/destination/folder"; // Windows端的目标文件夹路径

    upload_files(remote_host, username, password, remote_dir, local_dir);

    return 0;
}