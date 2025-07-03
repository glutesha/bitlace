<script lang="ts">
    import { toggleDelete } from "../delete";
    import { deletetool } from "../delete";
    import { pushSaves, save } from "../saves";

    async function onClick (){
        toggleDelete();
    }
</script>

<button on:click={onClick} class="bg-neutral-600 min-h-15 max-h-15 size-xl text-white text-3xl font-bold flex-1 transition duration-200 ease-in-out" class:bg-red-800={$deletetool}>Gallery</button>

