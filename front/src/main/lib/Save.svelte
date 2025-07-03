<script lang="ts">
    import { pushSaves, save } from "../saves";

    async function onClick (){
        save();
        await pushSaves();
    }
</script>

<button on:click={onClick} class=" bg-fuchsia-800 hover:bg-fuchsia-900 active:bg-fuchsia-950 rounded-3xl size-xl text-white px-5 py-3 text-3xl shadow-2xl font-bold shadow-black flex-1">Save</button>

