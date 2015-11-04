# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|

  config.vm.box = "ubuntu/trusty64"
  config.ssh.forward_x11 = true

  config.vm.synced_folder ".", "/development"

  config.vm.provider "virtualbox" do |vb|
    # Customize the amount of memory on the VM:
    vb.memory = "512"
  end

  config.vm.provision "shell", inline: <<-SHELL

    echo "cd /development" >> /home/vagrant/.bashrc

    function install_dep {
        sudo apt-get install -y $@
    }

    sudo apt-get update
    install_dep gcc-multilib
    sudo dpkg --add-architecture i386
    sudo apt-get update
    install_dep libc6:i386

    install_dep nasm
    install_dep xorriso
    install_dep qemu
  SHELL
end
