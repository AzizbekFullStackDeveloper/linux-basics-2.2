#include <stdio.h>
#include <stdlib.h>

void execute_command(const char *command) {
    int result = system(command);
    if (result == -1) {
        perror("Command execution failed");
        exit(EXIT_FAILURE);
    }
}

int main() {
    // Check if the user 'jane' exists
    printf("Checking if the user 'jane' exists...\n");
    if (system("id -u jane > /dev/null 2>&1") == 0) {
        printf("User 'jane' already exists.\n");
    } else {
        // Create the user 'jane'
        printf("Creating the user 'jane'...\n");
        execute_command("sudo useradd -m jane"); // -m creates a home directory
    }

    // Check if the home directory exists
    printf("Checking if the home directory '/home/jane' exists...\n");
    if (system("[ ! -d /home/jane ]") == 0) {
        printf("Home directory '/home/jane' does not exist. Creating...\n");
        execute_command("sudo mkdir -p /home/jane"); // Create home directory if it doesn't exist
        execute_command("sudo chown jane:jane /home/jane"); // Change ownership to jane
    }

    // Check if '.bashrc' exists for 'jane'
    printf("Checking if '.bashrc' exists for 'jane'...\n");
    if (system("sudo test -f /home/jane/.bashrc") != 0) {
        printf("Creating the '.bashrc' file for 'jane'...\n");
        FILE *file = fopen("/home/jane/.bashrc", "w");
        if (file) {
            fprintf(file, "export JANEFLAG=\"HD{Taqlid_qilish_bu_super!}\"\n");
            fclose(file);
            execute_command("sudo chown jane:jane /home/jane/.bashrc"); // Change ownership to jane
        } else {
            perror("Failed to create .bashrc");
            exit(EXIT_FAILURE);
        }
    } else {
        // If .bashrc exists, ensure the JANEFLAG is appended
        printf("Appending the JANEFLAG to '.bashrc' for 'jane'...\n");
        execute_command("echo 'export JANEFLAG=\"HD{Taqlid_qilish_bu_super!}\"' | sudo tee -a /home/jane/.bashrc > /dev/null");
        execute_command("sudo chown jane:jane /home/jane/.bashrc"); // Change ownership to jane
    }

    // Switch to user 'jane' and retrieve the JANEFLAG
    printf("Switching to user 'jane' and retrieving the JANEFLAG...\n");
    execute_command("sudo -i -u jane bash -c 'source ~/.bashrc; echo $JANEFLAG'");

    return 0;
}
